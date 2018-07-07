// ===================================================================
//
// Description		
//		Contains the definition of BaseVariable
//
// Revision history
//		Date			Description
//		30-Nov-2016		First version
//
// ===================================================================
#ifndef __BaseVariable__
#define __BaseVariable__

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

#include "../../Util/Common.h"
#include "Variable.h"
#include "VariableType.h"
#include "../Data/ISFSObject.h"
#include "../Data/ISFSArray.h"
#include "../Data/SFSArray.h"
#include "../Data/SFSObject.h"
#include "../../Exceptions/SFSError.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

namespace Sfs2X {
namespace Entities {
namespace Variables {

	// -------------------------------------------------------------------
	// Class BaseVariable
	// -------------------------------------------------------------------

	/// <summary>
	/// The BaseVariable object is the base class for all SmartFoxServer Variable entities on the client.
	/// </summary>
	/// 
	/// <seealso cref="Sfs2X.Entities.Variables.SFSUserVariable"/>
	/// <seealso cref="Sfs2X.Entities.Variables.SFSRoomVariable"/>
	/// <seealso cref="Sfs2X.Entities.Variables.SFSBuddyVariable"/>
	/// <seealso cref="Sfs2X.Entities.Variables.MMOItemVariable"/>
	class DLLImportExport BaseVariable : public Variable
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Creates a new BaseVariable instance.
		/// </summary>
		/// 
		/// <param name="name">The name of the Variable.</param>
		/// <param name="val">The value of the Variable.</param>
		/// <param name="type">The type of the Variable among those available in the <see cref="VariableType"/> class. Usually it is not necessary to pass this parameter, as the type is auto-detected from the value.</param>
		/// 
		/// <exclude/>
		BaseVariable(string name, boost::shared_ptr<void> val, long int type);

		/// <summary>
		/// Creates a new BaseVariable instance.
		/// </summary>
		/// 
		/// <param name="name">The name of the Variable.</param>
		/// <param name="val">The value of the Variable ( can be Boolean, int, Number, String, SFSObject, SFSArray ).</param>
		/// 
		/// <exclude/>
		BaseVariable(string name, boost::shared_ptr<long int> val);
		BaseVariable(string name, boost::shared_ptr<unsigned long int> val);
		BaseVariable(string name, boost::shared_ptr<int> val);
		BaseVariable(string name, boost::shared_ptr<unsigned int> val);
		BaseVariable(string name, boost::shared_ptr<bool> val);
		BaseVariable(string name, boost::shared_ptr<double> val);
		BaseVariable(string name, boost::shared_ptr<string> val);
		BaseVariable(string name, boost::shared_ptr<SFSObject> val);
		BaseVariable(string name, boost::shared_ptr<SFSArray> val);

		virtual ~BaseVariable();

		/// <inheritdoc />
		virtual boost::shared_ptr<string> Name();

		/// <inheritdoc />
		virtual VariableType Type();

		/// <inheritdoc />
		virtual boost::shared_ptr<void> Value();

		/// <inheritdoc />
		virtual boost::shared_ptr<bool> GetBoolValue();

		/// <inheritdoc />
		virtual boost::shared_ptr<long int> GetIntValue();

		/// <inheritdoc />
		virtual boost::shared_ptr<double> GetDoubleValue();

		/// <inheritdoc />
		virtual boost::shared_ptr<string> GetStringValue();

		/// <inheritdoc />
		virtual boost::shared_ptr<ISFSObject> GetSFSObjectValue();

		/// <inheritdoc />
		virtual boost::shared_ptr<ISFSArray> GetSFSArrayValue();

		/// <inheritdoc />
		virtual bool IsNull();

		virtual boost::shared_ptr<ISFSArray> ToSFSArray();

		boost::shared_ptr<string> TypeAsString();
		boost::shared_ptr<string> ValueAsString();

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

		void PopulateArrayWithValue(boost::shared_ptr<ISFSArray> arr);
		void SetValue(boost::shared_ptr<long int> val);
		void SetValue(boost::shared_ptr<unsigned long int> val);
		void SetValue(boost::shared_ptr<int> val);
		void SetValue(boost::shared_ptr<unsigned int> val);
		void SetValue(boost::shared_ptr<bool> val);
		void SetValue(boost::shared_ptr<double> val);
		void SetValue(boost::shared_ptr<string> val);
		void SetValue(boost::shared_ptr<SFSObject> val);
		void SetValue(boost::shared_ptr<SFSArray> val);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		/// <exclude/>
		boost::shared_ptr<string> name;

		/// <exclude/>
		VariableType type;

		/// <exclude/>
		boost::shared_ptr<void> val;
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
