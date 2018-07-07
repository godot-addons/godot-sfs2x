// ===================================================================
//
// Description		
//		Contains the definition of SFSUserVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSUserVariable__
#define __SFSUserVariable__

#include "../../Util/Common.h"
#include "BaseVariable.h"
#include "UserVariable.h"
#include "VariableType.h"
#include "../Data/ISFSObject.h"
#include "../Data/ISFSArray.h"
#include "../Data/SFSArray.h"
#include "../Data/SFSObject.h"
#include "../../Exceptions/SFSError.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace


using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Entities {
namespace Variables {

	/// <summary>
	/// The SFSUserVariable object represents a SmartFoxServer User Variable entity on the client.
	/// </summary>
	/// 
	/// <remarks>
	/// This is a custom value attached to a User object that gets automatically synchronized between client and server on every change.
	/// <para/>
	/// User Variables are particularly useful to store custom user data that must be "visible" to the other users, such as a profile, a score, a status message, etc.
	/// User Variables can be set by means of the <see cref="Sfs2X.Requests.SetUserVariablesRequest"/> request; they support the data types listed in the <seealso cref="VariableType"/> class (also nested). A User Variable can also be <c>null</c>.
	/// <para/>
	/// User Variables can be 'private' (starting from SFS2X v2.12 with client API v1.7): this flag allows to limit the visibility of variables to their owner only.
	/// In other words User Variables marked as private are not sent to other users, even if located in the same Room.
	/// </remarks>
	/// 
	/// <seealso cref="Sfs2X.Entities.User"/>
	/// <seealso cref="Sfs2X.Requests.SetUserVariablesRequest"/>
	class DLLImportExport SFSUserVariable : public BaseVariable, public UserVariable
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<UserVariable> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);

		/// <overrides>
		/// <summary>
		/// Contructor for SFSUserVariable
		/// </summary>
		/// </overrides>
		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		SFSUserVariable(string name, boost::shared_ptr<long int> val);
		SFSUserVariable(string name, boost::shared_ptr<unsigned long int> val);
		SFSUserVariable(string name, boost::shared_ptr<int> val);
		SFSUserVariable(string name, boost::shared_ptr<unsigned int> val);
		SFSUserVariable(string name, boost::shared_ptr<bool> val);
		SFSUserVariable(string name, boost::shared_ptr<double> val);
		SFSUserVariable(string name, boost::shared_ptr<string> val);
		SFSUserVariable(string name, boost::shared_ptr<SFSObject> val);
		SFSUserVariable(string name, boost::shared_ptr<SFSArray> val);

		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		/// <param name="type">
		/// it's usually not necessary to pass this parameter as the variable value is auto-detected
		/// </param>
		SFSUserVariable(string name, boost::shared_ptr<void> val, long int type);
		
		/// <summary>
		/// Creates a new private User Variable.
		/// </summary>
		/// 
		/// <remarks>
		/// Private User Variables are not broadcast to other users: they are only visible on the server side and in the owner's client application.
		/// </remarks>
		/// 
		/// <param name="name">The name of the User Variable.</param>
		/// <param name="val">The value of the User Variable.</param>
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<long int> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<unsigned long int> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<int> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<unsigned int> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<bool> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<double> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<string> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<SFSObject> val);
		static boost::shared_ptr<SFSUserVariable> newPrivateVariable(string name, boost::shared_ptr<SFSArray> val);

		virtual ~SFSUserVariable();

		bool IsPrivate();
		void IsPrivate(bool value);

		virtual boost::shared_ptr<string> Name();
		virtual VariableType Type();
		virtual boost::shared_ptr<void> Value();
		virtual boost::shared_ptr<bool> GetBoolValue();
		virtual boost::shared_ptr<long int> GetIntValue();
		virtual boost::shared_ptr<double> GetDoubleValue();
		virtual boost::shared_ptr<string> GetStringValue();
		virtual boost::shared_ptr<ISFSObject> GetSFSObjectValue();
		virtual boost::shared_ptr<ISFSArray> GetSFSArrayValue();
		virtual bool IsNull();
		virtual boost::shared_ptr<ISFSArray> ToSFSArray();
		virtual boost::shared_ptr<string> ToString();

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

		bool isPrivate;
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
