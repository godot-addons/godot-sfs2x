// ===================================================================
//
// Description		
//		Contains the implementation of an handler for a Tcp socket 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "TCPSocketLayer.h"
#include "../../Util/StringFormatter.h"
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {
namespace Sockets {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
TCPSocketLayer::TCPSocketLayer (boost::shared_ptr<BitSwarmClient> bs) 
{
	fsm = boost::shared_ptr<FiniteStateMachine>();
	connection = boost::shared_ptr<TCPClient>();
	ipAddress = boost::shared_ptr<IPAddress>();
	onConnect = boost::shared_ptr<ConnectionDelegate>();
	onDisconnect = boost::shared_ptr<ConnectionDelegate>();
	onError = boost::shared_ptr<OnErrorDelegate>();
	onData = boost::shared_ptr<OnDataDelegate>();

	isDisconnecting = false;
	isDisposed = false;

	log = bs->Log();
	bitSwarm = bs;
						
	InitStates();
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void TCPSocketLayer::Dispose()
{
	isDisposed = true;

	if (this->connection != NULL)
	{
		this->connection->Dispose();

		while (this->connection->CallbackCallInProgress() == true)
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		}
	}

	lockDispose.lock();

	this->log = boost::shared_ptr<Logger>();
	this->bitSwarm = boost::shared_ptr<BitSwarmClient>();
	this->me = boost::shared_ptr<TCPSocketLayer>();

	lockDispose.unlock();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
TCPSocketLayer::~TCPSocketLayer()
{
}

// -------------------------------------------------------------------
// InitStates
// -------------------------------------------------------------------
void TCPSocketLayer::InitStates() 
{
	fsm = boost::shared_ptr<FiniteStateMachine>(new FiniteStateMachine());

	std::vector<long int> states;
	for (long int enumerator = TCPSocketLayer::States_Disconnected; enumerator <= TCPSocketLayer::States_Connected; enumerator++)
	{
		states.push_back(enumerator);
	}
	fsm->AddAllStates(states);
			
	fsm->AddStateTransition(States_Disconnected, States_Connecting, Transitions_StartConnect);
	fsm->AddStateTransition(States_Connecting, States_Connected, Transitions_ConnectionSuccess);
	fsm->AddStateTransition(States_Connecting, States_Disconnected, Transitions_ConnectionFailure);
	fsm->AddStateTransition(States_Connected, States_Disconnected, Transitions_Disconnect);
				
	fsm->SetCurrentState(States_Disconnected);
}
		
// -------------------------------------------------------------------
// State
// -------------------------------------------------------------------
TCPSocketLayer::States TCPSocketLayer::State() 
{
	return (States)fsm->GetCurrentState();
}
			
// -------------------------------------------------------------------
// LogWarn
// -------------------------------------------------------------------
void TCPSocketLayer::LogWarn(boost::shared_ptr<string> msg) 
{
	lockDispose.lock();

	if (isDisposed == true)
	{
		lockDispose.unlock();
		return;
	}

	if (log == NULL) 
	{
		lockDispose.unlock();
		return;
	}
	
	boost::shared_ptr<std::vector<string> > messages (new std::vector<string>());
	messages->push_back("TCPSocketLayer: ");
	messages->push_back(*msg);

	log->Warn(messages);

	lockDispose.unlock();
}
		
// -------------------------------------------------------------------
// LogError
// -------------------------------------------------------------------
void TCPSocketLayer::LogError(boost::shared_ptr<string> msg) 
{
	lockDispose.lock();

	if (isDisposed == true)
	{
		lockDispose.unlock();
		return;
	}

	if (log == NULL)
	{
		lockDispose.unlock();
		return;
	}

	boost::shared_ptr<std::vector<string> > messages (new std::vector<string>());
	messages->push_back("TCPSocketLayer: ");
	messages->push_back(*msg);

	log->Error(messages);

	lockDispose.unlock();
}

// -------------------------------------------------------------------
// HandleError
// -------------------------------------------------------------------
void TCPSocketLayer::HandleError(boost::shared_ptr<string> err) 
{
	HandleError(err, SocketErrors_NotSocket);
}

// -------------------------------------------------------------------
// HandleError
// -------------------------------------------------------------------
void TCPSocketLayer::HandleError(boost::shared_ptr<string> err, SocketErrors se) 
{
	lockDispose.lock();

	if (isDisposed == true)
	{
		lockDispose.unlock();
		return;
	}

	boost::shared_ptr<std::map<string, boost::shared_ptr<void> > > data (new std::map<string, boost::shared_ptr<void> >());
	data->insert(std::pair<string, boost::shared_ptr<void> >("err", err));
	
	stringstream converterIntToString;
	converterIntToString << (long int)se;
	boost::shared_ptr<string> convertedString (new string(converterIntToString.str()));
	data->insert(std::pair<string, boost::shared_ptr<void> >("se", convertedString));

	boost::shared_ptr<ParameterizedThreadStart> callback (new ParameterizedThreadStart(&TCPSocketLayer::HandleErrorCallback, (unsigned long long)this));
	boost::shared_ptr<ThreadManager> manager = bitSwarm->ThreadManager(); 
	if (manager != NULL)
	{
		manager->EnqueueCustom(callback, data);
	}

	lockDispose.unlock();
}

// -------------------------------------------------------------------
// HandleErrorCallback
// -------------------------------------------------------------------
void TCPSocketLayer::HandleErrorCallback(unsigned long long context, boost::shared_ptr<void> state) 
{
	// Map context
	TCPSocketLayer* instance = (TCPSocketLayer*)context;

	boost::shared_ptr<std::map<string, boost::shared_ptr<void> > > data = (boost::static_pointer_cast<std::map<string, boost::shared_ptr<void> > >)(state);
	boost::shared_ptr<string> err = (boost::static_pointer_cast<string>)((*data)["err"]);

	long int errAsInteger = 0;
	
	boost::shared_ptr<string> format (new string("%d"));
	StringFormatter<long int> ((boost::static_pointer_cast<string>)((*data)["se"]), format, errAsInteger);
		
	SocketErrors se = (SocketErrors)errAsInteger;
			
	instance->fsm->ApplyTransition(Transitions_ConnectionFailure);

	// Dont spam errors when disconnecting
	if (!instance->isDisconnecting) 
	{
		instance->LogError(err);
		instance->CallOnError(err, se);
	}

	instance->HandleDisconnection();
}

// -------------------------------------------------------------------
// HandleDisconnection
// -------------------------------------------------------------------
void TCPSocketLayer::HandleDisconnection() 
{
	if (State() == States_Disconnected) 
	{
		return;
	}

	fsm->ApplyTransition(Transitions_Disconnect);
	CallOnDisconnect();
}

// -------------------------------------------------------------------
// CallOnError
// -------------------------------------------------------------------
void TCPSocketLayer::CallOnError(boost::shared_ptr<string> msg, SocketErrors se) 
{
	if (onError != NULL) 
	{
		onError->Invoke(msg, se);
	}
}

// -------------------------------------------------------------------
// CallOnData
// -------------------------------------------------------------------
void TCPSocketLayer::CallOnData(boost::shared_ptr<vector<unsigned char> > data) 
{
	lockDispose.lock();

	if (isDisposed == true)
	{
		lockDispose.unlock();
		return;
	}

	if (onData != NULL) 
	{
		boost::shared_ptr<ThreadManager> manager = bitSwarm->ThreadManager(); 
		if (manager != NULL)
		{
			manager->EnqueueDataCall(onData, data);
		}
	}

	lockDispose.unlock();
}

// -------------------------------------------------------------------
// CallOnConnect
// -------------------------------------------------------------------
void TCPSocketLayer::CallOnConnect() 
{
	if (onConnect != NULL) 
	{
		onConnect->Invoke();
	}
}

// -------------------------------------------------------------------
// CallOnDisconnect
// -------------------------------------------------------------------
void TCPSocketLayer::CallOnDisconnect() 
{
	if (onDisconnect != NULL) 
	{
		onDisconnect->Invoke();
	}
}

// -------------------------------------------------------------------
// OnSocketConnection
// -------------------------------------------------------------------
void TCPSocketLayer::OnSocketConnection(unsigned long long context, SocketErrors code)
{
	// Map context
	TCPSocketLayer* instance = (TCPSocketLayer*)context;

	if (code == SocketErrors_Success)
	{
		// Connection established

		// Notify connection result
		instance->fsm->ApplyTransition(Transitions_ConnectionSuccess);
		instance->CallOnConnect();

		// Schedule an asynchronous read
		boost::shared_ptr<TCPDataReadDelegate> callback (new TCPDataReadDelegate(&TCPSocketLayer::OnSocketDataReceived, context));
		instance->connection->AsynchRead(callback);
	}
	else
	{
		boost::shared_ptr<string> message (new string("Connection error: "));
		instance->HandleError(message, code);	
	}
}


// -------------------------------------------------------------------
// OnSocketDataSent
// -------------------------------------------------------------------
void TCPSocketLayer::OnSocketDataSent(unsigned long long context, SocketErrors code)
{
	// Map context
	TCPSocketLayer* instance = (TCPSocketLayer*)context;

	if (code != SocketErrors_Success) 
	{
		boost::shared_ptr<string> message (new string("Error sending data to remote side over the established connection"));
		instance->HandleError(message, code);	
    }
}

// -------------------------------------------------------------------
// OnSocketDataReceived
// -------------------------------------------------------------------
void TCPSocketLayer::OnSocketDataReceived(unsigned long long context, boost::shared_ptr<vector<unsigned char> > data)
{
	// Map context
	TCPSocketLayer* instance = (TCPSocketLayer*)context;

	if (data->size() < 1) 
	{
		boost::shared_ptr<string> message (new string("Connection closed by the remote side"));
		instance->HandleError(message);
		return;
    }

	instance->HandleBinaryData(data);

	// Schedule an asynchronous read
	boost::shared_ptr<TCPDataReadDelegate> callback (new TCPDataReadDelegate(&TCPSocketLayer::OnSocketDataReceived, context));
	instance->connection->AsynchRead(callback);
}

// -------------------------------------------------------------------
// HandleBinaryData
// -------------------------------------------------------------------
void TCPSocketLayer::HandleBinaryData(boost::shared_ptr<vector<unsigned char> > data) 
{
	CallOnData(data);
}

// -------------------------------------------------------------------
// SocketPollSleep
// -------------------------------------------------------------------
void TCPSocketLayer::SocketPollSleep (long int value)
{
	socketPollSleep = value;
}

// -------------------------------------------------------------------
// SocketPollSleep
// -------------------------------------------------------------------
long int TCPSocketLayer::SocketPollSleep()
{
	return socketPollSleep;
}

// -------------------------------------------------------------------
// WriteSocket
// -------------------------------------------------------------------
void TCPSocketLayer::WriteSocket(boost::shared_ptr<vector<unsigned char> > data)
{
	if (State() != States_Connected) 
	{
		boost::shared_ptr<string> message (new string("Trying to write to disconnected socket"));
		LogError(message);	

		data->clear();
		return;
	}

	try
	{
		boost::shared_ptr<TCPDataWriteDelegate> callback (new TCPDataWriteDelegate(&TCPSocketLayer::OnSocketDataSent, (unsigned long long)this));
		connection->AsynchWrite(data, callback);
	}
	catch (...)
	{
		data->clear();

		boost::shared_ptr<string> message (new string("General error writing to socket: "));
		HandleError(message);
	}
}

// ISocketLayer implementation

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void TCPSocketLayer::Connect(boost::shared_ptr<IPAddress> address, unsigned short int port)
{
	if (State() != States_Disconnected) 
	{
		boost::shared_ptr<string> message (new string("Calling connect when the socket is not disconnected"));
		LogWarn(message);	
		return;
	}

	if (bitSwarm == NULL)
	{
		return;
	}

	socketNumber = port;
	ipAddress = address;
			
	fsm->ApplyTransition(Transitions_StartConnect);

	try
	{
		// Below we create a TCPClient instance that will be used as connection to exchange data with remote SmartFoxServer
		// At API startup we have not a connection entity up to the below statement will be executed
		// but when an API reconnection occurs we already have a "pending" connection
		// To avoid that asynch callbacks (data received or data written callbacks) will be called on instance disposed by smart pointers
		// we must sure that no callbacks are in progress and we mark the instance as disposed before create a new TCPClient 
		if (connection != NULL)
		{
			connection->Dispose();

			while (connection->CallbackCallInProgress() == true)
			{
				boost::this_thread::sleep(boost::posix_time::milliseconds(100));
			}
		}

		connection = boost::shared_ptr<TCPClient>(new TCPClient(*(bitSwarm->GetBoostService())));

		this->me = shared_from_this();
		boost::shared_ptr<TCPConnectionDelegate> callback (new TCPConnectionDelegate(&TCPSocketLayer::OnSocketConnection, (unsigned long long)this));
		connection->Connect(ipAddress, socketNumber, Const_TimeoutConnect, callback);

		bitSwarm->GetBoostService()->reset();
		boost::thread t(boost::bind(static_cast<size_t (boost::asio::io_service::*)()>(&boost::asio::io_service::run), bitSwarm->GetBoostService()));
	}
	catch (...)
	{
		boost::shared_ptr<string> message (new string("General exception on connection: "));
		HandleError(message);
	}
}

// -------------------------------------------------------------------
// IsConnected
// -------------------------------------------------------------------
bool TCPSocketLayer::IsConnected()
{
	return State() == States_Connected;
}

// -------------------------------------------------------------------
// RequiresConnection
// -------------------------------------------------------------------
bool TCPSocketLayer::RequiresConnection()
{
	return true;
}

// -------------------------------------------------------------------
// Disconnect
// -------------------------------------------------------------------
void TCPSocketLayer::Disconnect()
{
	if (State() != States_Connected) 
	{
		boost::shared_ptr<string> message (new string("Calling disconnect when the socket is not connected"));
		LogWarn(message);	
		return;
	}

	isDisconnecting = true;
			
    while (this->connection->CallbackCallInProgress() == true)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }

	try 
	{
		connection->Shutdown();
	}
	catch (...)
	{
	}

	HandleDisconnection();
	isDisconnecting = false;
}

// -------------------------------------------------------------------
// OnConnect
// -------------------------------------------------------------------
boost::shared_ptr<ConnectionDelegate> TCPSocketLayer::OnConnect()
{
	return onConnect;
}

// -------------------------------------------------------------------
// OnConnect
// -------------------------------------------------------------------
void TCPSocketLayer::OnConnect(boost::shared_ptr<ConnectionDelegate> onConnect)
{
	this->onConnect = onConnect;
}

// -------------------------------------------------------------------
// OnDisconnect
// -------------------------------------------------------------------
boost::shared_ptr<ConnectionDelegate> TCPSocketLayer::OnDisconnect()
{
	return onDisconnect;
}

// -------------------------------------------------------------------
// OnDisconnect
// -------------------------------------------------------------------
void TCPSocketLayer::OnDisconnect(boost::shared_ptr<ConnectionDelegate> onDisconnect)
{
	this->onDisconnect = onDisconnect;
}

// -------------------------------------------------------------------
// Write
// -------------------------------------------------------------------
void TCPSocketLayer::Write(boost::shared_ptr<vector<unsigned char> > data)
{
	WriteSocket(data);
}

// -------------------------------------------------------------------
// OnData
// -------------------------------------------------------------------
boost::shared_ptr<OnDataDelegate> TCPSocketLayer::OnData()
{
	return onData;
}

// -------------------------------------------------------------------
// OnData
// -------------------------------------------------------------------
void TCPSocketLayer::OnData(boost::shared_ptr<OnDataDelegate> onData)
{
	this->onData = onData;
}

// -------------------------------------------------------------------
// OnError
// -------------------------------------------------------------------
boost::shared_ptr<OnErrorDelegate> TCPSocketLayer::OnError()
{
	return onError;
}

// -------------------------------------------------------------------
// OnError
// -------------------------------------------------------------------
void TCPSocketLayer::OnError(boost::shared_ptr<OnErrorDelegate> onError)
{
		this->onError = onError;
}

// -------------------------------------------------------------------
// Kill
// -------------------------------------------------------------------
void TCPSocketLayer::Kill()
{
	isDisconnecting = true;
			
    while (this->connection->CallbackCallInProgress() == true)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }

	try 
	{
		connection->Shutdown();
	}
	catch (...)
	{
	}

	HandleDisconnection();
	isDisconnecting = false;
}

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X
