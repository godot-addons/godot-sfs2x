// ===================================================================
//
// Description		
//		Contains the definition of ConfigData
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ConfigData__
#define __ConfigData__

#include "./Common.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {

	/// <summary>
	/// The ConfigData class stores the client configuration data loaded from an external XML file or passed directly to the deputy connect method.
	/// </summary>
	/// 
	/// <remarks>
	/// The external configuration file is loaded by the <em>SmartFox</em> class when its <see cref="Sfs2X.SmartFox.LoadConfig()">SmartFox->LoadConfig()</see> method is called.
	/// Otherwise it can be passed directly to one of the <see cref="Sfs2X.SmartFox.Connect(ConfigData)">SmartFox->Connect(ConfigData)</see> method overloads of the <em>SmartFox</em> class.
	/// </remarks>
	class DLLImportExport ConfigData
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		ConfigData();

		/// <summary>
		/// Get the IP address or host name of the SmartFoxServer 2X instance to connect to (TCP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>127.0.0.1</c>.
		/// </remarks>
		string Host();

		/// <summary>
		/// Specifies the IP address or host name of the SmartFoxServer 2X instance to connect to (TCP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>127.0.0.1</c>.
		/// </remarks>
		void Host(string value);

		/// <summary>
		/// Get the TCP port of the SmartFoxServer 2X instance to connect to (TCP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>9933</c>.
		/// </remarks>
		unsigned short int Port();

		/// <summary>
		/// Specifies the TCP port of the SmartFoxServer 2X instance to connect to (TCP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>9933</c>.
		/// </remarks>
		void Port(unsigned short int value);

		/// <summary>
		/// Get the IP address of the SmartFoxServer 2X instance to connect to (UDP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>127.0.0.1</c>.
		/// </remarks>
		string UdpHost();

		/// <summary>
		/// Specifies the IP address of the SmartFoxServer 2X instance to connect to (UDP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>127.0.0.1</c>.
		/// </remarks>
		void UdpHost(string value);

		/// <summary>
		/// Get the UDP port of the SmartFoxServer 2X instance to connect to (UDP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>9933</c>.
		/// </remarks>
		unsigned short int UdpPort();

		/// <summary>
		/// Specifies the UDP port of the SmartFoxServer 2X instance to connect to (UDP connection).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>9933</c>.
		/// </remarks>
		void UdpPort(unsigned short int value);

		/// <summary>
		/// Get the Zone of the SmartFoxServer 2X instance to join.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>null</c>.
		/// </remarks>
		string Zone();

		/// <summary>
		/// Specifies the Zone of the SmartFoxServer 2X instance to join.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>null</c>.
		/// </remarks>
		void Zone(string value);

		/// <summary>
		/// Get the state for the client-server messages debug.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>false</c>.
		/// </remarks>
		bool Debug();

		/// <summary>
		/// Indicates whether the client-server messages debug should be enabled or not.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>false</c>.
		/// </remarks>
		void Debug(bool value);

		/// <summary>
		/// Get the port for generic HTTP communication.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>8080</c>.
		/// </remarks>
		unsigned short int HttpPort();

		/// <summary>
		/// Specifies the port for generic HTTP communication.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>8080</c>.
		/// </remarks>
		void HttpPort(unsigned short int value);

		/// <summary>
		/// Get the port for HTTPS communication.
		/// </summary>
		/// 
		/// <remarks>
		/// For example this parameter is required during the initialization of an encrypted connection.
		/// The default value is <c>8443</c>.
		/// </remarks>
		unsigned short int HttpsPort();

		/// <summary>
		/// Specifies the port for HTTPS communication.
		/// </summary>
		/// 
		/// <remarks>
		/// For example this parameter is required during the initialization of an encrypted connection.
		/// The default value is <c>8443</c>.
		/// </remarks>
		void HttpsPort(unsigned short int value);

		/// <summary>
		/// Get the state for the SmartFoxServer's BlueBox.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>true</c>.
		/// </remarks>
		bool UseBlueBox();

		/// <summary>
		/// Indicates whether the SmartFoxServer's BlueBox should be enabled or not.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>true</c>.
		/// </remarks>
		void UseBlueBox(bool value);

		/// <summary>
		/// Get the BlueBox polling speed.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>750</c>.
		/// </remarks>
		long int BlueBoxPollingRate();

		/// <summary>
		/// Specifies the BlueBox polling speed.
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>750</c>.
		/// </remarks>
		void BlueBoxPollingRate(long int value);

		/// <summary>
		/// Gets selected IPv4 or IPv6 mode to connect to the SmartFoxServer 2X instance (TCP and UDP connections).
		/// </summary>
		/// 
		/// <remarks>
		/// The default value is <c>false</c>.
		/// </remarks>
		bool ForceIPv6();

		/// <summary>
		/// Selects the usage of IPv4 or IPv6 to connect to the SmartFoxServer 2X instance (TCP and UDP connections).
		/// </summary>
		/// 
		/// <remarks>
		/// Set <c>false</c> to select IPv4; <c>true</c> for IPv6
		/// The default value is <c>false</c>.
		/// </remarks>
		void ForceIPv6(bool value);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

		
	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<string> host;
		unsigned short int port;
		boost::shared_ptr<string> udpHost;
		unsigned short int udpPort;
		boost::shared_ptr<string> zone;
		bool debug;
		
		unsigned short int httpPort;
		unsigned short int httpsPort;
		bool useBlueBox;
		long int blueBoxPollingRate;
		bool forceIPv6;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
