// ===================================================================
//
// Description		
//		Contains the definition of Logger 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __Logger__
#define __Logger__

namespace Sfs2X {
namespace Logging {
	class Logger;
}	// namespace Logging
}	// namespace Sfs2X

#include "LogLevel.h"
#include "LoggerEvent.h"
#include "../SmartFox.h"
#include "../Util/EventDispatcher.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer
#include <boost/thread/recursive_mutex.hpp>	// Boost recursive mutex

// STL library settings
#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
#include <vector>				// STL library: vector object
#include <map>					// STL library: map object
using namespace std;			// Declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Logging {

	// -------------------------------------------------------------------
	// Class Logger
	// -------------------------------------------------------------------
	/// <summary>
	/// The internal logger used by the SmartFoxServer 2X client API.
	/// </summary>
	/// <remarks>
	/// You can get a reference to the Logger by means of the <see cref="Sfs2X.SmartFox.Logger">SmartFox.Logger</see> property.
	/// Accessing the logger can be useful to control the client-side logging level, enable or disable the events dispatching.
	/// When logger events are enabled, you can add your own listners to this class, in order to have a lower access to logged messages (for example you could display them in a dedicated panel in the application interface).
	/// </remarks>
	/// 
	/// <seealso cref="LoggerEvent"/>
	/// <seealso cref="Sfs2X.SmartFox.Logger"/> 
	class DLLImportExport Logger
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		Logger(boost::shared_ptr<SmartFox> smartFox);
		void Dispose();

		/*
		/// <summary>
		/// Indicates whether or not the output of logged messages to the console is enabled.
		/// </summary>
		bool EnableConsoleTrace();
		void EnableConsoleTrace(bool value);
		*/

		/// <summary>
		/// Indicates whether dispatching of log events is enabled or not.
		/// </summary>
		/// 
		/// <seealso cref="LoggerEvent"/>
		bool EnableEventDispatching();
		void EnableEventDispatching(bool value);

		/// <summary>
		/// Determines the current logging level.
		/// </summary>
		/// 
		/// <remarks>
		/// Messages with a level lower than this value are not logged. The available log levels are contained in the <see cref="LogLevel"/> class.
		/// </remarks>
		/// 
		/// <seealso cref="LogLevel"/>
		LogLevel LoggingLevel();
		void LoggingLevel(LogLevel value);

		void Debug(boost::shared_ptr<std::vector<string> > messages);
		void Info(boost::shared_ptr<std::vector<string> > messages);
		void Warn(boost::shared_ptr<std::vector<string> > messages);
		void Error(boost::shared_ptr<std::vector<string> > messages);

		/// <summary>
		/// Registers a delegate method for log messages callbacks.
		/// </summary>
		/// 
		/// <remarks>
		/// Calling this method is just like calling the <see cref="Sfs2X.SmartFox.AddLogListener">SmartFox.AddLogListener</see> method. 
		/// </remarks>
		/// 
		/// <param name="level">The level of the log events to register a listener for.</param>
		/// <param name="listener">The event listener to register.</param>
		/// 
		/// <example>
		/// <code>
		/// void SomeMethod() {
		/// 	sfs->Logger()->EnableEventDispatching(true);
		/// 	sfs->Logger()->AddEventListener(Sfs2X::Logging::LOGLEVEL_INFO, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(OnInfoLogMessage, (unsigned long long) this)));
		/// 	sfs->Logger()->AddEventListener(Sfs2X::Logging::LOGLEVEL_WARN, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(OnWarnLogMessage, (unsigned long long) this)));
		/// }
		/// 
		/// void OnInfoLogMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
		///		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///		boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///		boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
        /// }
		/// 
		/// void OnWarnLogMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
		///		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///		boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///		boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		/// }
		/// </code>
		/// </example>
		/// 
		/// <seealso cref="Sfs2X.SmartFox.AddLogListener"/>
		void AddEventListener(LogLevel level, boost::shared_ptr<EventListenerDelegate> listener);

		/// <summary>
		/// Removes a delegate method for log messages callbacks.
		/// </summary>
		/// 
		/// <remarks>
		/// Calling this method is just like calling the <see cref="Sfs2X.SmartFox.RemoveLogListener">Sfs2X.SmartFox.RemoveLogListener</see> method. 
		/// </remarks>
		/// 
		/// <param name="logLevel">The level of the log events to remove the listener for.</param>
		/// <param name="listener">The event listener to remove.</param>
		/// 
		/// <seealso cref="Sfs2X.SmartFox.RemoveLogListener"/>
		void RemoveEventListener(LogLevel logLevel, boost::shared_ptr<EventListenerDelegate> listener);

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

		void Log(LogLevel level, boost::shared_ptr<string> message);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<SmartFox> smartFox;
		LogLevel loggingLevel;
		//bool enableConsoleTrace;
		bool enableEventDispatching; 
		boost::recursive_mutex lockDispose;
	};
}	// namespace Logging
}	// namespace Sfs2X

#endif
