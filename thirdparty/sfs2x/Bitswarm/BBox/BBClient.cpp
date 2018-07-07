// ===================================================================
//
// Description		
//		Contains the implementation of BBClient
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#if defined(_MSC_VER)
#pragma warning(disable:4996)			// disable warning 4996
#endif

#include "BBClient.h"
#include "BBEvent.h"
#include "../../Util/StringFormatter.h"

#include <boost/system/error_code.hpp> 
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>

using namespace boost::archive::iterators;

namespace Sfs2X {
namespace Bitswarm {
namespace BBox {

boost::shared_ptr<string> BBClient::BB_SERVLET (new string("BlueBox/BlueBox.do"));
boost::shared_ptr<string> BBClient::BB_DEFAULT_HOST (new string("localhost"));
boost::shared_ptr<string> BBClient::BB_NULL (new string("null"));
boost::shared_ptr<string> BBClient::CMD_CONNECT (new string("connect"));
boost::shared_ptr<string> BBClient::CMD_POLL (new string("poll"));
boost::shared_ptr<string> BBClient::CMD_DATA (new string("data"));
boost::shared_ptr<string> BBClient::CMD_DISCONNECT (new string("disconnect"));
boost::shared_ptr<string> BBClient::ERR_INVALID_SESSION (new string("err01"));
boost::shared_ptr<string> BBClient::SFS_HTTP (new string("sfsHttp"));

const static char SEP = '|';

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BBClient::BBClient(boost::shared_ptr<BitSwarmClient> bs)
{
	this->isConnected = false;
	this->host = boost::shared_ptr<string>(new string(*BB_DEFAULT_HOST));
	this->port = BB_DEFAULT_PORT;
	this->bbUrl = boost::shared_ptr<string>();
	this->debug = bs->Debug();
	this->sessId = boost::shared_ptr<string>();
	this->pollSpeed = DEFAULT_POLL_SPEED;
	this->log = bs->Log();
	io_service_pollTimer = boost::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());
	//this->pollTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(*(bs->GetBoostService())));
	this->pollTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(*io_service_pollTimer));
	this->boostService = bs->GetBoostService();
}

// -------------------------------------------------------------------
// Initialize
// -------------------------------------------------------------------
void BBClient::Initialize()
{
	// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
	// so any initialization that need of instance shared pointer should be moved into this method that will be explicity called after constructor

	this->dispatcher = boost::shared_ptr<EventDispatcher>(new EventDispatcher(shared_from_this()));
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void BBClient::Dispose()
{
	this->log = boost::shared_ptr<Logger>();

	if (pollTimer != NULL)
	{
		pollTimer->cancel();
		pollTimer = boost::shared_ptr<boost::asio::deadline_timer>();
	}

	if (this->dispatcher != NULL)
	{
		this->dispatcher->Dispose();
		this->dispatcher = boost::shared_ptr<EventDispatcher>();
	}
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Getters / Setters
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// -------------------------------------------------------------------
// IsConnected
// -------------------------------------------------------------------
bool BBClient::IsConnected()
{
	return sessId != NULL;
}

// -------------------------------------------------------------------
// IsDebug
// -------------------------------------------------------------------
bool BBClient::IsDebug()
{
	return debug;
}

// -------------------------------------------------------------------
// IsDebug
// -------------------------------------------------------------------
void BBClient::IsDebug(bool value)
{
	debug = value;
}

// -------------------------------------------------------------------
// Host
// -------------------------------------------------------------------
boost::shared_ptr<string> BBClient::Host()
{
	return host;
}
		
// -------------------------------------------------------------------
// Port
// -------------------------------------------------------------------
unsigned short int BBClient::Port()
{
	return port;
}

// -------------------------------------------------------------------
// SessionId
// -------------------------------------------------------------------
boost::shared_ptr<string> BBClient::SessionId()
{
	return sessId;
}

// -------------------------------------------------------------------
// PollSpeed
// -------------------------------------------------------------------
long int BBClient::PollSpeed()
{
	return pollSpeed;
}

// -------------------------------------------------------------------
// PollSpeed
// -------------------------------------------------------------------
void BBClient::PollSpeed(long int value)
{
	pollSpeed = (value >= MIN_POLL_SPEED && value <= MAX_POLL_SPEED) ? value : DEFAULT_POLL_SPEED;
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Public methods
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void BBClient::Connect (boost::shared_ptr<string> host, unsigned short int port)
{
	if (isConnected)
		boost::throw_exception(boost::enable_error_info (std::runtime_error("BlueBox session is already connected"))); 

	this->host = host;
	this->port = port;

	char buffer[512];
	sprintf (buffer, "http://%s:%ld/%s", host->c_str(), port, BB_SERVLET->c_str());

	bbUrl = boost::shared_ptr<string>(new string(buffer));

	if (debug) {
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		boost::shared_ptr<string> logMessage (new string());
	
		boost::shared_ptr<string> format (new string("[ BB-Connect ]: %s"));
		StringFormatter<const char*> (logMessage, format, bbUrl->c_str());
			
		logMessages->push_back(*logMessage);
		log->Debug(logMessages);
	}

	SendRequest (CMD_CONNECT);
}

void BBClient::Send (boost::shared_ptr<ByteArray> binData)
{
	if (!isConnected)
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Can't send data, BlueBox connection is not active"))); 
			
	SendRequest (CMD_DATA, binData);
}

void BBClient::Close()
{
	HandleConnectionLost(true);
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Private methods
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void BBClient::OnHttpResponse (unsigned long long context, bool error, boost::shared_ptr<string> response)
{
	BBClient* instance = (BBClient*)context;

	if (error) 
	{
		boost::shared_ptr<BBEvent> evt (new BBEvent(BBEvent::IO_ERROR));
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > parameters (new map<string, boost::shared_ptr<void> >());
		parameters->insert(pair<string, boost::shared_ptr<void> >("message", response));
		evt->Params(parameters);
		instance->HandleConnectionLost(true);
		instance->DispatchEvent(evt);
		return;
	}

	try {
		if (instance->debug)
		{
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			boost::shared_ptr<string> logMessage (new string());
	
			boost::shared_ptr<string> format (new string("[ BB-Receive ]: %s"));
			StringFormatter<const char*> (logMessage, format, response->c_str());
			
			logMessages->push_back(*logMessage);
			instance->log->Debug(logMessages);
		}

		// Obtain splitted params
		vector<string> reqBits; 

		int start = 0, end = 0;
		while ((end = response->find(SEP, start)) != string::npos) 
		{
			reqBits.push_back(response->substr(start, end - start));
			start = end + 1;
		}
		reqBits.push_back(response->substr(start));

		if (reqBits.size() < 2) {
			return;
		}

		boost::shared_ptr<string> cmd (new string(reqBits[0]));
		boost::shared_ptr<string> data (new string(reqBits[1]));

		if ((*cmd) == (*CMD_CONNECT)) 
		{
			instance->sessId = data;
			instance->isConnected = true;

			boost::shared_ptr<BBEvent> evt (new BBEvent(BBEvent::CONNECT));
			instance->DispatchEvent(evt);

			// Start the polling cycle
			instance->Poll(boost::system::error_code());
		} else if ((*cmd) == (*CMD_POLL)) {
			boost::shared_ptr<ByteArray> binData = boost::shared_ptr<ByteArray>();

			// Decode Base64-Encoded string to real ByteArray
			if ((*data) != *BB_NULL) {
				binData = instance->DecodeResponse(data);
			}

			if ((*data) != (*BB_NULL)) {
				// Dispatch the event
				boost::shared_ptr<BBEvent> evt (new BBEvent(BBEvent::DATA));
				boost::shared_ptr<map<string, boost::shared_ptr<void> > > parameters (new map<string, boost::shared_ptr<void> >());
				parameters->insert(pair<string, boost::shared_ptr<void> >("data", binData));
				evt->Params(parameters);
				instance->DispatchEvent(evt);
			}

			// Pre-launch next polling request
			if (instance->isConnected) {
				instance->io_service_pollTimer->reset();
				instance->pollTimer->expires_from_now(boost::posix_time::milliseconds(instance->pollSpeed));
				instance->pollTimer->async_wait(boost::bind(&BBClient::Poll, instance, boost::asio::placeholders::error));
				instance->io_service_pollTimer->run();
			}
		} else if ((*cmd) == (*ERR_INVALID_SESSION)) 
		{
			boost::shared_ptr<BBEvent> evt (new BBEvent(BBEvent::IO_ERROR));
			boost::shared_ptr<map<string, boost::shared_ptr<void> > > parameters (new map<string, boost::shared_ptr<void> >());
			boost::shared_ptr<string> message (new string("Invalid http session !"));
			parameters->insert(pair<string, boost::shared_ptr<void> >("message", message));
			evt->Params(parameters);
			instance->HandleConnectionLost(false);
			instance->DispatchEvent(evt);
			return;
		}
	} catch (exception e) {
		//calling e.Result will throw an exception at the local scope when it encouters something like a 404 or a 405
		boost::shared_ptr<BBEvent> evt (new BBEvent(BBEvent::IO_ERROR));
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > parameters (new map<string, boost::shared_ptr<void> >());
		boost::shared_ptr<string> messageException (new string(e.what()));
		parameters->insert(pair<string, boost::shared_ptr<void> >("message", messageException));
		evt->Params(parameters);
		instance->HandleConnectionLost(false);
		instance->DispatchEvent(evt);
		return;
	}
}

void BBClient::Poll (const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Timer has been stopped
		// Nothing to do
		return;
	}

	// Timer is expired

	if (isConnected) {
		SendRequest (CMD_POLL);
	}
}

void BBClient::SendRequest (boost::shared_ptr<string> cmd)
{
	SendRequest (cmd, boost::shared_ptr<void>());
}

void BBClient::SendRequest (boost::shared_ptr<string> cmd, boost::shared_ptr<void> data)
{
	// Encode request variables
	boost::shared_ptr<string> encodedData = EncodeRequest (cmd, data);
	boost::shared_ptr<string> escapedData = UrlEncode(encodedData);

	if (debug) {
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		boost::shared_ptr<string> logMessage (new string());
	
		boost::shared_ptr<string> format (new string("[ BB-Send ]: %s"));
		StringFormatter<const char*> (logMessage, format, encodedData->c_str());
			
		logMessages->push_back(*logMessage);
		log->Debug(logMessages);
	}

	// Create HTTP loader and send
	boost::shared_ptr<SFSWebClient> webClient = GetWebClient ();
	webClient->UploadValuesAsync (this->host, this->port, SFS_HTTP, escapedData);
}

boost::shared_ptr<string> BBClient::UrlEncode(boost::shared_ptr<string> data)
{
	static std::string allowed_chars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");

	std::stringstream ss;
	ss << std::hex;
	for (std::string::const_iterator ci = data->begin(); ci != data->end(); ++ci)
	{
		if (allowed_chars.find(*ci) != std::string::npos)
		{
			ss << *ci;
		}
		else if (*ci == ' ')
		{
			ss << '+';
		}
		else
		{
			ss << '%' << std::setfill('0') << std::setw(2) << std::right << static_cast<int>(*ci);
		}
	}
	
	boost::shared_ptr<string> encoded(new string(ss.str()));
	return encoded;
}

boost::shared_ptr<string> BBClient::UrlDecode(boost::shared_ptr<string> data)
{
	std::stringstream ss;

	for (char const * p_read = data->c_str(), *p_end = (data->c_str() + data->size()); p_read < p_end; p_read++)
	{
		if (p_read[0] == '%' && p_read + 1 != p_end && p_read + 2 != p_end && isXdigit(p_read[1]) && isXdigit(p_read[2]))
		{
			ss << static_cast<char>((((p_read[1] & 0xf) + ((p_read[1] >= 'A') ? 9 : 0)) << 4) | ((p_read[2] & 0xf) + ((p_read[2] >= 'A') ? 9 : 0)));
			p_read += 2;
		}
		else if (p_read[0] == '+')
		{
			// Undo the encoding that replaces spaces with plus signs.
			ss << ' ';
		}
		else
		{
			ss << p_read[0];
		}
	}

	boost::shared_ptr<string> decoded(new string(ss.str()));
	return decoded;
}


bool BBClient::isXdigit(char c)
{
	return  (c >= '0' && c <= '9') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z');
}

boost::shared_ptr<SFSWebClient> BBClient::GetWebClient()
{
	boost::shared_ptr<SFSWebClient> webClient (new SFSWebClient (*boostService));
	boost::shared_ptr<HttpResponseDelegate> delegateResponse (new HttpResponseDelegate(&BBClient::OnHttpResponse, (unsigned long long)this));
	webClient->OnHttpResponse(delegateResponse);

	return webClient;
}

void BBClient::HandleConnectionLost (bool fireEvent)
{
	if (isConnected) 
	{
		isConnected = false;
		sessId = boost::shared_ptr<string>();
		pollTimer->cancel();

		// Fire event to Bitswarm client
		if (fireEvent)
		{
			boost::shared_ptr<BaseEvent> evt (new BBEvent (BBEvent::DISCONNECT));
			DispatchEvent (evt);
		}
	}
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Message Codec
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
boost::shared_ptr<string> BBClient::EncodeRequest (boost::shared_ptr<string> cmd)
{
	return EncodeRequest (cmd, boost::shared_ptr<void>());
}

boost::shared_ptr<string> BBClient::EncodeRequest (boost::shared_ptr<string> cmd, boost::shared_ptr<void> data)
{
	boost::shared_ptr<string> encoded (new string());
	boost::shared_ptr<string> stringData;

	if (cmd == NULL)
		cmd = BB_NULL;

	if (data == NULL) {
		stringData = BB_NULL;
	}
	//	else if (dynamic_cast<ByteArray*>(data) != NULL) {
	else {
		boost::shared_ptr<vector<unsigned char> > dataToConvert = ((boost::static_pointer_cast<ByteArray>)(data))->Bytes();

		// Pad with 0 until a multiple of 3
		unsigned int paddedCharacters = 0;
		while(dataToConvert->size() % 3 != 0)
		{
			paddedCharacters++;
			dataToConvert->push_back(0x00);
		}

		typedef base64_from_binary<transform_width<const unsigned char *, 6, 8> > base64_encoder;

		// Encode the buffer and create a string
		boost::shared_ptr<unsigned char> arrayToConvert (new unsigned char[dataToConvert->size()], array_deleter<unsigned char>());
		std::copy(dataToConvert.get()->begin(), dataToConvert.get()->end(), arrayToConvert.get());

		string encodedString(
			base64_encoder(arrayToConvert.get()),
			base64_encoder(arrayToConvert.get() + (dataToConvert->size() - paddedCharacters)));

/*
		string encodedString(
			base64_encoder(&((*dataToConvert)[0])),
			base64_encoder(&((*dataToConvert)[0]) + (dataToConvert->size() - paddedCharacters)));
*/
		// Add '=' for each padded character used
		for(unsigned int i = 0; i < paddedCharacters; i++)
		{
			encodedString.push_back('=');
		}

		stringData = boost::shared_ptr<string>(new string(encodedString));
	}

	encoded->append((sessId == NULL ? (*BB_NULL) : (*sessId)));
	encoded->append(&SEP);
	encoded->append(*cmd);
	encoded->append(&SEP);
	encoded->append(*stringData);

	return encoded;
}

boost::shared_ptr<ByteArray> BBClient::DecodeResponse (boost::shared_ptr<string> rawData)
{
	/*
	if (rawData.substr(0, SFS_HTTP.length) != SFS_HTTP)
	throw new ArgumentError("Unexpected Response format. Missing BlueBox header: " + (rawData.length < 1024 ? rawData : "[too big data]"));
	*/

	typedef transform_width<binary_from_base64<remove_whitespace<string::const_iterator> >, 8, 6 > base64_decoder;

	unsigned int paddChars = count(rawData->begin(), rawData->end(), '=');
	std::replace(rawData->begin(), rawData->end(), '=', 'A');							// replace '=' by base64 encoding of '\0'
	string result(base64_decoder(rawData->begin()), base64_decoder(rawData->end()));	// decode
	result.erase(result.end() - paddChars, result.end());								// erase padding '\0' characters

	boost::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>(result.begin(), result.end()));

	return boost::shared_ptr<ByteArray>(new ByteArray(data));
}


void BBClient::AddEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener)
{
	this->dispatcher->AddEventListener(eventType, listener);
}


boost::shared_ptr<EventDispatcher> BBClient::Dispatcher()
{
	return this->dispatcher;
}

void BBClient::DispatchEvent(boost::shared_ptr<BaseEvent> evt)
{
	this->dispatcher->DispatchEvent(evt);
}


}	// namespace BBox
}	// namespace Bitswarm
}	// namespace Sfs2X


