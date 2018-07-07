// ===================================================================
//
// Description		
//		Contains the implementation of an handler for a Tcp client SSL
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// =================================================================== 
#include "TCPClientSSL.h"

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
#include <boost/detail/interlocked.hpp>			// Boost Asio header
#endif

namespace Sfs2X {
namespace Core {
namespace Sockets {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
TCPClientSSL::TCPClientSSL (boost::asio::io_service& io_service, boost::asio::ssl::context& context)
	: boostIoService(io_service),
	  boostTcpResolver(io_service),
      boostTcpSocket(io_service, context),
	  boostTimerTaskDeadline(io_service)
{
	this->isDisposed = false;
	this->isCallbackCallInProgress = false;
	callbackTCPConnection = boost::shared_ptr<TCPConnectionDelegate>();
	callbackTCPDataRead = boost::shared_ptr<TCPDataReadDelegate>();
	callbackTCPDataWrite = boost::shared_ptr<TCPDataWriteDelegate>();
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_EXCHANGE(&counterAsyncReadOperationsInProgress, 0);
		BOOST_INTERLOCKED_EXCHANGE(&counterAsyncWriteOperationsInProgress, 0);
	#else
		counterAsyncReadOperationsInProgress = 0;
		counterAsyncWriteOperationsInProgress = 0;
	#endif

    boostTcpSocket.set_verify_mode(boost::asio::ssl::verify_peer);
    boostTcpSocket.set_verify_callback(boost::bind(&TCPClientSSL::OnBoostAsioVerifyCertificate, this, _1, _2));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
TCPClientSSL::~TCPClientSSL()
{
	// Wait for completion of asynchronous operations 
	long int counterInProgressAsyncRead = counterAsyncReadOperationsInProgress = 0;
	long int counterInProgressAsyncWrite = counterAsyncWriteOperationsInProgress = 0;
	do
	{
		counterInProgressAsyncRead = counterAsyncReadOperationsInProgress;
		counterInProgressAsyncWrite = counterAsyncWriteOperationsInProgress;
	} while ((counterInProgressAsyncRead > 0) || (counterInProgressAsyncWrite > 0));
	//MAX while ((counterAsyncReadOperationsInProgress > 0) || (counterAsyncWriteOperationsInProgress > 0));
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void TCPClientSSL::Dispose()
{
	this->isDisposed = true;
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void TCPClientSSL::Connect (boost::shared_ptr<IPAddress> ipAddress, unsigned short int ipPort, long int timeout, boost::shared_ptr<TCPConnectionDelegate> callback)
{
	if (this->isDisposed == true)
	{
		return;
	}

	// Preserve callback that will be used to notify tcp connection result
	callbackTCPConnection = callback;

	// Start deadline timer for tcp connection task
    boostTimerTaskDeadline.expires_from_now(boost::posix_time::seconds(timeout));
	boostTimerTaskDeadline.async_wait(boost::bind(&TCPClientSSL::OnBoostAsioConnectTimedout, this, boost::asio::placeholders::error));

	// Attempt to establish a tcp connection
	//boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(*(ipAddress->Address())), ipPort);

	std::stringstream ss;
	ss << ipPort;
    boost::asio::ip::tcp::resolver::query query(*(ipAddress->Address()), ss.str());
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = boostTcpResolver.resolve(query);

	boost::asio::async_connect(boostTcpSocket.lowest_layer(), endpoint_iterator,  boost::bind(&TCPClientSSL::OnBoostAsioConnect, this, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void TCPClientSSL::SynchConnect (boost::shared_ptr<IPAddress> ipAddress, unsigned short int ipPort)
{
	boost::system::error_code error;

	if (this->isDisposed == true)
	{
		return;
	}

	// Attempt to establish a tcp connection
	//boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(*(ipAddress->Address())), ipPort);

	std::stringstream ss;
	ss << ipPort;
    boost::asio::ip::tcp::resolver::query query(*(ipAddress->Address()), ss.str());
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = boostTcpResolver.resolve(query);

	boost::asio::connect(boostTcpSocket.lowest_layer(), endpoint_iterator, error);

    if (!error)
    {
	    boostTcpSocket.set_verify_mode(boost::asio::ssl::context::verify_none);
		boostTcpSocket.handshake(boost::asio::ssl::stream_base::client, error);
    }
}

// -------------------------------------------------------------------
// Shutdown
// -------------------------------------------------------------------
void TCPClientSSL::Shutdown()
{
	// Cancel all asynchronous operations associated with the socket
    boostTcpSocket.lowest_layer().close();
    //boostIoService.stop();
}

// -------------------------------------------------------------------
// OnBoostAsioVerifyCertificate
// -------------------------------------------------------------------
bool TCPClientSSL::OnBoostAsioVerifyCertificate(bool preverified, boost::asio::ssl::verify_context& ctx)
{
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.

    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

    return preverified;
}

// -------------------------------------------------------------------
// OnBoostAsioConnect
// -------------------------------------------------------------------
void TCPClientSSL::OnBoostAsioConnect(const boost::system::error_code& code)
{
	// Stop deadline timer for tcp connection task
	boostTimerTaskDeadline.cancel();

	this->isCallbackCallInProgress = true;

	if (this->isDisposed == true)
	{
		this->isCallbackCallInProgress = false;
		return;
	}

	// Notify the establishment of the tcp connection
	callbackTCPConnection->Invoke((SocketErrors)(code.value()));

	this->isCallbackCallInProgress = false;

    if (!code)
    {
		boostTcpSocket.async_handshake(boost::asio::ssl::stream_base::client, boost::bind(&TCPClientSSL::OnBoostAsioHandleHandshake, this, boost::asio::placeholders::error));
    }
}

// -------------------------------------------------------------------
// OnBoostAsioHandleHandshake
// -------------------------------------------------------------------
void TCPClientSSL::OnBoostAsioHandleHandshake(const boost::system::error_code& error)
{
	// quando questo metodo è stato chiamato si può iniziare a fare send/receive
}

// -------------------------------------------------------------------
// OnBoostAsioConnectTimedout
// -------------------------------------------------------------------
void TCPClientSSL::OnBoostAsioConnectTimedout(const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Deadline timer for tcp connection task has been stopped
		// Nothing to do
		return;
	}

	// Deadline timer for tcp connection task is expired

	this->isCallbackCallInProgress = true;

	if (this->isDisposed == true)
	{
		this->isCallbackCallInProgress = false;
		return;
	}

	// Notify the establishment of the tco connection
	callbackTCPConnection->Invoke((SocketErrors)(code.value()));

	this->isCallbackCallInProgress = false;
}

// -------------------------------------------------------------------
// AsynchRead
// -------------------------------------------------------------------
void TCPClientSSL::AsynchRead (boost::shared_ptr<TCPDataReadDelegate> callback)
{
	if (this->isDisposed == true)
	{
		return;
	}

	// Preserve callback that will be used to notify tcp received data
	
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	callbackTCPDataRead = callback;

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Schedule asyncronous read
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_INCREMENT(&counterAsyncReadOperationsInProgress);
	#else
		counterAsyncReadOperationsInProgress++;
	#endif
	boostTcpSocket.async_read_some(boost::asio::buffer(boostTcpInputBuffer), boost::bind(&TCPClientSSL::OnBoostAsioDataReceived, this, _1, _2));
}

// -------------------------------------------------------------------
// SynchRead
// -------------------------------------------------------------------
boost::shared_ptr<vector<unsigned char> > TCPClientSSL::SynchRead ()
{
	size_t length = 0;
	boost::system::error_code error;
	
	if (this->isDisposed == true)
	{
		return boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
	}

	length = boostTcpSocket.read_some(boost::asio::buffer(boostTcpInputBuffer), error);

	if (error == boost::asio::error::eof)
	{
		return boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());			// Connection closed cleanly by peer
	}
	else if (error)
	{
		throw boost::system::system_error(error);	// Some other error.
	}

	boost::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>());
	if (length > 0)
	{
		data->assign((unsigned char*)(boostTcpInputBuffer.data()), (unsigned char*)(boostTcpInputBuffer.data() + length));
	}

	return data;
}

// -------------------------------------------------------------------
// AsynchWrite
// -------------------------------------------------------------------
void TCPClientSSL::AsynchWrite (boost::shared_ptr<vector<unsigned char> > data, boost::shared_ptr<TCPDataWriteDelegate> callback)
{
	if (this->isDisposed == true)
	{
		return;
	}

	// Preserve callback that will be used to notify the completion of tcp write data

	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	callbackTCPDataWrite = callback;

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Allocate a smart pointer to a vector where take place outgoing data
	boost::shared_ptr<unsigned char> bufferOutput(new unsigned char[data->size()], array_deleter<unsigned char>());

	unsigned char* writerBufferOutput = bufferOutput.get();
	long int offsetBufferOutput = 0;
	vector<unsigned char>::iterator iterator;
	for(iterator = data->begin(); iterator != data->end(); ++iterator)
	{
		*(writerBufferOutput + offsetBufferOutput) = (*iterator);
		offsetBufferOutput++;
	}
	//memcpy ((void*)(bufferOutput.get()), data->data(), data->size());

	// Schedule an asynchronous write to dispatch outgoing data over Tcp socket
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_INCREMENT(&counterAsyncWriteOperationsInProgress);
	#else
		counterAsyncWriteOperationsInProgress++;	
	#endif
	boostTcpSocket.async_write_some(boost::asio::buffer((void*)bufferOutput.get(), (size_t)data->size()), boost::bind(&TCPClientSSL::OnBoostAsioDataSent, this, bufferOutput, data->size(), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// SynchWrite
// -------------------------------------------------------------------
void TCPClientSSL::SynchWrite (boost::shared_ptr<vector<unsigned char> > data)
{
	if (this->isDisposed == true)
	{
		return;
	}

	// Allocate a smart pointer to a vector where take place outgoing data
	boost::shared_ptr<unsigned char> bufferOutput(new unsigned char[data->size()], array_deleter<unsigned char>());

	unsigned char* writerBufferOutput = bufferOutput.get();
	long int offsetBufferOutput = 0;
	vector<unsigned char>::iterator iterator;
	for(iterator = data->begin(); iterator != data->end(); ++iterator)
	{
		*(writerBufferOutput + offsetBufferOutput) = (*iterator);
		offsetBufferOutput++;
	}

	// Dispatch outgoing data over Tcp socket
	boostTcpSocket.write_some (boost::asio::buffer((void*)bufferOutput.get(), (size_t)data->size()));
}

// -------------------------------------------------------------------
// OnBoostAsioDataSent
// -------------------------------------------------------------------
void TCPClientSSL::OnBoostAsioDataSent(boost::shared_ptr<unsigned char> bufferOutput, size_t length, size_t transferred, const boost::system::error_code& error)
{
	this->isCallbackCallInProgress = true;

	if (this->isDisposed == true)
	{
		this->isCallbackCallInProgress = false;
		return;
	}

	// Notify operation status
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	if (callbackTCPDataWrite != NULL)
	{
		callbackTCPDataWrite->Invoke((SocketErrors)error.value());
	}

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Check if all output data have been transmitted
	if (transferred != length)
	{
		// Not all data have been transmitted

		// Allocate a smart pointer to a vector where take place outgoing data
		boost::shared_ptr<unsigned char> bufferNextOutput(new unsigned char[length - transferred], array_deleter<unsigned char>());
		memcpy ((void*)(bufferNextOutput.get()), bufferOutput.get() + transferred, length - transferred);

		// Schedule an asynchronous write to dispatch outgoing data over Tcp socket
		boostTcpSocket.async_write_some(boost::asio::buffer((void*)bufferNextOutput.get(), (length - transferred)), boost::bind(&TCPClientSSL::OnBoostAsioDataSent, this, bufferNextOutput, (length - transferred), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));

		this->isCallbackCallInProgress = false;

		return;
	}

	// Decrease counter of asynchronous write that are in progress
	if (counterAsyncWriteOperationsInProgress > 0)
	{
		#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
			BOOST_INTERLOCKED_DECREMENT(&counterAsyncWriteOperationsInProgress);
		#else
			counterAsyncWriteOperationsInProgress--;
		#endif
	}
		
	this->isCallbackCallInProgress = false;
}

// -------------------------------------------------------------------
// OnBoostAsioDataReceived
// -------------------------------------------------------------------
void TCPClientSSL::OnBoostAsioDataReceived(const boost::system::error_code& error, long int length)
{
	this->isCallbackCallInProgress = true;

	if (this->isDisposed == true)
	{
		this->isCallbackCallInProgress = false;
		return;
	}

	boost::shared_ptr<vector<unsigned char> > data;
	if (length > 0)
	{
		data = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
		data->assign((unsigned char*)(boostTcpInputBuffer.data()), (unsigned char*)(boostTcpInputBuffer.data() + length));
	}
	else
	{
		data = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
	}

	// Notify received data
	// Note that data length could be 0 when socket closure has been detected
	 
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	if (callbackTCPDataRead != NULL)
	{
		callbackTCPDataRead->Invoke(data);
	}

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Decrease counter of asynchronous read that are in progress
	if (counterAsyncReadOperationsInProgress > 0)
	{
		#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
			BOOST_INTERLOCKED_DECREMENT(&counterAsyncReadOperationsInProgress);
		#else
			counterAsyncReadOperationsInProgress--;
		#endif
	}

	this->isCallbackCallInProgress = false;
}

// -------------------------------------------------------------------
// CallbackCallInProgress
// -------------------------------------------------------------------
bool TCPClientSSL::CallbackCallInProgress()
{
	return isCallbackCallInProgress;
}

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X
