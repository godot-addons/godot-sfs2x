// ===================================================================
//
// Description		
//		Helper class for crypting
//
// Revision history
//		Date			Description
//		01-May-2015		First version
//
// ===================================================================
#define BOOST_THREAD_USES_MOVE

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <boost/asio/ssl.hpp>
#include "CryptoInitializer.h"
#include "CryptoKey.h"
#include "../Core/Sockets/TCPClientSSL.h"				// SSL TCP client handler

using namespace boost::archive::iterators;

namespace Sfs2X {
	namespace Util {

		boost::shared_ptr<string> CryptoInitializer::KEY_SESSION_TOKEN (new string("SessToken"));
		boost::shared_ptr<string> CryptoInitializer::TARGET_SERVLET (new string("BlueBox/CryptoManager"));

		// -------------------------------------------------------------------
		// Constructor
		// -------------------------------------------------------------------
		CryptoInitializer::CryptoInitializer(boost::shared_ptr<SmartFox> sfs)
		{
			this->useHttps = true;
			this->key = boost::shared_ptr<string>();
			this->errorMessage = nullptr;

			// These are not events because they should fail at test time
			if (!sfs->IsConnected())
				boost::throw_exception(boost::enable_error_info (std::runtime_error("Cryptography cannot be initialized before connecting to SmartFoxServer!"))); 

			if (sfs->GetSocketEngine()->CryptoKey() != NULL)
				boost::throw_exception(boost::enable_error_info (std::runtime_error("Cryptography is already initialized!"))); 

			this->sfs = sfs;
		}

		// -------------------------------------------------------------------
		// Run
		// -------------------------------------------------------------------
		void CryptoInitializer::Run()
		{
			RunHelper();
		}

		// -------------------------------------------------------------------
		// RunHelper
		// -------------------------------------------------------------------
		void CryptoInitializer::RunHelper()
		{
			// To grant linux compatibility, below statements have been replaced with RunHelperSSLAsync/RunHelperAsync methods that return a bool instead of the key session string 
			// The new implementation of RunHelperSSLAsync/RunHelperAsync store key session in a local member (see key member)
			/*
			boost::future<boost::shared_ptr<string> > f = boost::async(boost::bind((useHttps ? &CryptoInitializer::RunHelperSSLAsync : &CryptoInitializer::RunHelperAsync), this));

			// Wait for asynch compution of RunHelperAsync, then process returned value as http response
			OnHttpResponse(f.get());
			*/

			boost::future<bool> f = boost::async(boost::launch::async, boost::bind((useHttps ? &CryptoInitializer::RunHelperSSLAsync : &CryptoInitializer::RunHelperAsync), this));

			bool result = f.get();

			if (result && !errorMessage)
			{
				// Wait for asynch compution of RunHelperAsync, then process returned value as http response
				OnHttpResponse(this->key);
			}
			else
			{
				if(errorMessage) {
					OnHttpError(errorMessage);
				} else {
					OnHttpError(boost::shared_ptr<string>(new string("Error retrieving crypto key from SFS2X")));
				}
			}
		}

		// -------------------------------------------------------------------
		// RunHelperAsync
		// -------------------------------------------------------------------
		bool CryptoInitializer::RunHelperAsync()
		{
			bool returned = false;
			boost::shared_ptr<TCPClient> client = boost::shared_ptr<TCPClient>();

			try 
			{
				client = boost::shared_ptr<TCPClient>(new TCPClient(*(sfs->GetBoostService())));

				boost::shared_ptr<IPAddress> address(new IPAddress(*sfs->GetIPAddress(sfs->Config()->Host(), (useHttps ? sfs->Config()->HttpsPort() : sfs->Config()->HttpPort()))));

				client->SynchConnect(address, (useHttps ? sfs->Config()->HttpsPort() : sfs->Config()->HttpPort()));
			}
			catch (exception e) 
			{
				boost::shared_ptr<string> messageException (new string(e.what()));
				boost::shared_ptr<string> message (new string("Http error creating http connection: " + (*messageException)));

				this->errorMessage = message;

				try 
				{
					client->Shutdown();
				}
				catch (exception e) 
				{
					boost::shared_ptr<string> messageException (new string(e.what()));
					boost::shared_ptr<string> message (new string("Error during http scocket shutdown: " + (*messageException)));

					this->errorMessage = message;
				}

				return returned;
			}

			try
			{
				string data = (*KEY_SESSION_TOKEN) + "=" + (*sfs->SessionToken());

				boost::shared_ptr<wstring> dataAsNative (new wstring());
				dataAsNative->assign(data.begin(), data.end());

				boost::shared_ptr<string> dataAsUtf8 (new string());
				WStrToUtf8(dataAsNative, dataAsUtf8);

				string sb;
				sb.append("POST /" + (*CryptoInitializer::TARGET_SERVLET) + " HTTP/1.0\r\n");
				sb.append("Content-Type: application/x-www-form-urlencoded; charset=utf-8\r\n");

				boost::shared_ptr<string> valueContentLength (new string());
				boost::shared_ptr<string> format (new string ("Content-Length: %ld\r\n"));
				StringFormatter<long int> (valueContentLength, format, (long int)dataAsUtf8->size());

				sb.append(*valueContentLength);
				sb.append("\r\n");
				sb.append(data);

				boost::shared_ptr<vector<unsigned char> > outputData (new vector<unsigned char>(sb.begin(), sb.end()));
				outputData->push_back('\0');

				client->SynchWrite(outputData);

				string responseFromServer;
				do
				{
					boost::shared_ptr<vector<unsigned char> > receive = client->SynchRead();
					if (receive->size() == 0)
					{
						break;
					}

					boost::shared_ptr<string> src (new string(receive->begin(), receive->end()));
					boost::shared_ptr<wstring> dest (new wstring());
					Utf8toWStr(src, dest);

					responseFromServer.append(dest->begin(), dest->end());

				} while (true);

				// Remove http header and trim whitespaces at the end
				std::vector<string> parts;

				const char* chunkCurrent = responseFromServer.c_str();
				const char* chunkNext = chunkCurrent;

				while ((chunkNext = strstr(chunkCurrent, "\r\n\r\n")) != NULL) 
				{
					string tokenizedValue (chunkCurrent, chunkNext - chunkCurrent);
					parts.push_back(tokenizedValue);
					chunkCurrent = chunkNext + 4;
				}

				string tokenizedValueLast (chunkCurrent);
				if (tokenizedValueLast.length() > 0)
				{
					parts.push_back(tokenizedValueLast);
				}

				if ((responseFromServer.size() > 4) && (responseFromServer.compare(responseFromServer.size() - 4, 4, "\r\n\r\n") == 0))
				{
					parts.push_back("");
				}

				if (parts.size() < 2) {
					this->errorMessage = boost::shared_ptr<string>(new string ("Error during http response: connection closed by remote side"));
					return returned;
				}

				string charsToTrim = " ";
				string dataPayload = parts[1].substr(0, parts[1].find_last_not_of(charsToTrim) + 1);

				this->key = boost::shared_ptr<string>(new string(dataPayload));
				returned = true;
			}
			catch (exception e) 
			{
				boost::shared_ptr<string> messageException (new string(e.what()));
				boost::shared_ptr<string> message (new string("Error during http request: " + (*messageException)));

				this->errorMessage = message;
			}

			try 
			{
				client->Shutdown();
			}
			catch (exception e) 
			{
				boost::shared_ptr<string> messageException (new string(e.what()));
				boost::shared_ptr<string> message (new string("Error during http scocket shutdown: " + (*messageException)));

				this->errorMessage = message;
			}

			return returned;
		}

		// -------------------------------------------------------------------
		// RunHelperSSLAsync
		// -------------------------------------------------------------------
		bool CryptoInitializer::RunHelperSSLAsync()
		{
			bool returned = false;
			boost::shared_ptr<TCPClientSSL> client = boost::shared_ptr<TCPClientSSL>();

			try 
			{
				// Create a context that uses the default paths for
				// finding CA certificates.
				boost::asio::ssl::context contextSSL(boost::asio::ssl::context::sslv23);
				contextSSL.set_default_verify_paths();
				//contextSSL.load_verify_file("ca.pem");

				client = boost::shared_ptr<TCPClientSSL>(new TCPClientSSL(*(sfs->GetBoostService()), contextSSL));

				boost::shared_ptr<IPAddress> address(new IPAddress(*sfs->GetIPAddress(sfs->Config()->Host(), (useHttps ? sfs->Config()->HttpsPort() : sfs->Config()->HttpPort()))));

				client->SynchConnect(address, (useHttps ? sfs->Config()->HttpsPort() : sfs->Config()->HttpPort()));
			}
			catch (exception e) 
			{
				boost::shared_ptr<string> messageException (new string(e.what()));
				boost::shared_ptr<string> message (new string("Http error creating http connection: " + (*messageException)));

				this->errorMessage = message;

				try 
				{
					client->Shutdown();
				}
				catch (exception e) 
				{
					boost::shared_ptr<string> messageException (new string(e.what()));
					boost::shared_ptr<string> message (new string("Error during http scocket shutdown: " + (*messageException)));

					this->errorMessage = message;
				}

				return returned;
			}

			try
			{
				string data = (*KEY_SESSION_TOKEN) + "=" + (*sfs->SessionToken());

				boost::shared_ptr<wstring> dataAsNative (new wstring());
				dataAsNative->assign(data.begin(), data.end());

				boost::shared_ptr<string> dataAsUtf8 (new string());
				WStrToUtf8(dataAsNative, dataAsUtf8);

				string sb;
				sb.append("POST /" + (*CryptoInitializer::TARGET_SERVLET) + " HTTP/1.0\r\n");
				sb.append("Content-Type: application/x-www-form-urlencoded; charset=utf-8\r\n");

				boost::shared_ptr<string> valueContentLength (new string());
				boost::shared_ptr<string> format (new string ("Content-Length: %ld\r\n"));
				StringFormatter<long int> (valueContentLength, format, (long int)dataAsUtf8->size());

				sb.append(*valueContentLength);
				sb.append("\r\n");
				sb.append(data);

				boost::shared_ptr<vector<unsigned char> > outputData (new vector<unsigned char>(sb.begin(), sb.end()));
				outputData->push_back('\0');

				client->SynchWrite(outputData);

				string responseFromServer;
				do
				{
					boost::shared_ptr<vector<unsigned char> > receive = client->SynchRead();
					if (receive->size() == 0)
					{
						break;
					}

					boost::shared_ptr<string> src (new string(receive->begin(), receive->end()));
					boost::shared_ptr<wstring> dest (new wstring());
					Utf8toWStr(src, dest);

					responseFromServer.append(dest->begin(), dest->end());

				} while (true);

				// Remove http header and trim whitespaces at the end
				std::vector<string> parts;

				const char* chunkCurrent = responseFromServer.c_str();
				const char* chunkNext = chunkCurrent;

				while ((chunkNext = strstr(chunkCurrent, "\r\n\r\n")) != NULL) 
				{
					string tokenizedValue (chunkCurrent, chunkNext - chunkCurrent);
					parts.push_back(tokenizedValue);
					chunkCurrent = chunkNext + 4;
				}

				string tokenizedValueLast (chunkCurrent);
				if (tokenizedValueLast.length() > 0)
				{
					parts.push_back(tokenizedValueLast);
				}

				if ((responseFromServer.size() > 4) && (responseFromServer.compare(responseFromServer.size() - 4, 4, "\r\n\r\n") == 0))
				{
					parts.push_back("");
				}

				if (parts.size() < 2) {
					this->errorMessage = boost::shared_ptr<string>(new string ("Error during http response: connection closed by remote side"));
					return returned;
				}

				string charsToTrim = " ";
				string dataPayload = parts[1].substr(0, parts[1].find_last_not_of(charsToTrim) + 1);

				this->key = boost::shared_ptr<string>(new string(dataPayload));
				returned = true;
			}
			catch (exception e) 
			{
				boost::shared_ptr<string> messageException (new string(e.what()));
				boost::shared_ptr<string> message (new string("Error during http request: " + (*messageException)));

				this->errorMessage = message;
			}

			try 
			{
				client->Shutdown();
			}
			catch (exception e) 
			{
				boost::shared_ptr<string> messageException (new string(e.what()));
				boost::shared_ptr<string> message (new string("Error during http scocket shutdown: " + (*messageException)));

				this->errorMessage = message;
			}

			return returned;
		}

		// -------------------------------------------------------------------
		// OnHttpResponse
		// -------------------------------------------------------------------
		void CryptoInitializer::OnHttpResponse(boost::shared_ptr<string> rawData)
		{
			boost::shared_ptr<ByteArray> byteData = boost::shared_ptr<ByteArray>();
			byteData = DecodeResponse(rawData);

			boost::shared_ptr<ByteArray> key (new ByteArray());
			boost::shared_ptr<ByteArray> iv (new ByteArray());

			// Extract the key and init vector and pass them to the BitSwarmClient
			boost::shared_ptr<vector<unsigned char> > keyValues (new vector<unsigned char>());
			byteData->Position(0);
			byteData->ReadBytes(0, 16, *keyValues.get());
			key->WriteBytes(keyValues);

			boost::shared_ptr<vector<unsigned char> > ivValues (new vector<unsigned char>());
			byteData->Position(0);
			byteData->ReadBytes(16, 16, *ivValues.get());
			iv->WriteBytes(ivValues);

			boost::shared_ptr<CryptoKey> cryptoKey (new CryptoKey(iv, key));
			sfs->GetSocketEngine()->CryptoKey(cryptoKey);

			boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

			boost::shared_ptr<bool> value (new bool());
			*value = true;
			evtParams->insert(pair<string, boost::shared_ptr<void> >("success", value));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::CRYPTO_INIT, evtParams));
			sfs->DispatchEvent(evt);
		}

		// -------------------------------------------------------------------
		// OnHttpError
		// -------------------------------------------------------------------
		void CryptoInitializer::OnHttpError(boost::shared_ptr<string> errorMsg)
		{
			boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

			boost::shared_ptr<bool> value (new bool());
			*value = false;
			evtParams->insert(pair<string, boost::shared_ptr<void> >("success", value));

			evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::CRYPTO_INIT, evtParams));
			sfs->DispatchEvent(evt);
		}

		// -------------------------------------------------------------------
		// DecodeResponse
		// -------------------------------------------------------------------
		boost::shared_ptr<ByteArray> CryptoInitializer::DecodeResponse (boost::shared_ptr<string> rawData)
		{

			typedef transform_width<binary_from_base64<remove_whitespace<string::const_iterator> >, 8, 6 > base64_decoder;

			unsigned int paddChars = (unsigned int)count(rawData->begin(), rawData->end(), '=');
			std::replace(rawData->begin(), rawData->end(), '=', 'A');							// replace '=' by base64 encoding of '\0'
			string result(base64_decoder(rawData->begin()), base64_decoder(rawData->end()));	// decode
			result.erase(result.end() - paddChars, result.end());								// erase padding '\0' characters

			boost::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>(result.begin(), result.end()));

			return boost::shared_ptr<ByteArray>(new ByteArray(data));
		}

	}	// namespace Util
}	// namespace Sfs2X
