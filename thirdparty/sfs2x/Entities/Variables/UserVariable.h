// ===================================================================
//
// Description		
//		Contains the definition of UserVariable interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __UserVariable__
#define __UserVariable__

#include "../../Util/Common.h"
#include "Variable.h"
#include "VariableType.h"
#include "../Data/ISFSObject.h"
#include "../Data/ISFSArray.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {
namespace Variables {

	/// <summary>
	/// The UserVariable interface defines all the public methods and properties that an object representing a SmartFoxServer User Variable exposes.
	/// </summary>
	/// 
	/// <remarks>
	/// In the SmartFoxServer 2X client API this interface is implemented by the <see cref="SFSUserVariable"/> class. Read the class description for additional informations.
	/// </remarks>
	/// 
	/// <seealso cref="Variable"/>
	class DLLImportExport UserVariable : public Variable
	{
	public:

		/// <summary>
		/// Indicates whether this User Variable is private or not.
		/// </summary>
		/// 
		/// <remarks>
		/// A private User Variable is visible only to its owner; any changes made to the variable will be transmitted to the owner only.
		/// <para/>
		/// <b>NOTE</b>: setting this property manually on an existing User Variable returned by the API has no effect on the server and can disrupt the API functioning.
		/// This flag can be set when the User Variable object is created by the developer only (using the <em>new</em> keyword).
		/// </remarks>
		virtual bool IsPrivate() = 0;

		/// <summary>
		/// Indicates whether this User Variable is private or not.
		/// </summary>
		/// 
		/// <remarks>
		/// A private User Variable is visible only to its owner; any changes made to the variable will be transmitted to the owner only.
		/// <para/>
		/// <b>NOTE</b>: setting this property manually on an existing User Variable returned by the API has no effect on the server and can disrupt the API functioning.
		/// This flag can be set when the User Variable object is created by the developer only (using the <em>new</em> keyword).
		/// </remarks>
		virtual void IsPrivate(bool value) = 0;
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
