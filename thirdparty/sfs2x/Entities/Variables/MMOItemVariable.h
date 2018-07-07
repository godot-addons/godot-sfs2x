// ===================================================================
//
// Description		
//		Contains the definition of MMOItemVariable
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __MMOItemVariable__
#define __MMOItemVariable__

#include "../../Util/Common.h"
#include "BaseVariable.h"
#include "IMMOItemVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

	/// <summary>
	/// The MMOItemVariable object represents a SmartFoxServer MMOItem Variable entity on the client.
	/// </summary>
	/// 
	/// <remarks>
	/// An MMOItem Variable is a custom value attached to an MMOItem object that gets automatically synchronized between client and server on every change, provided that the MMOItem is inside the Area of Interest of the current user in a MMORoom.
	/// <para />
	/// <b>NOTE:</b> MMOItem Variables behave exactly like User Variables and support the same data types, but they can be created, updated and deleted on the server side only.
	/// </remarks>
	/// 
	/// <seealso cref="Sfs2X.Entities.MMOItem"/>
	/// <seealso cref="Sfs2X.Entities.MMORoom"/>
	class DLLImportExport MMOItemVariable : public BaseVariable, public IMMOItemVariable
	{
	public:
		
		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <exclude/>
		static boost::shared_ptr<IMMOItemVariable> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);

		/// <exclude/>
		MMOItemVariable(string name, boost::shared_ptr<void> val, long int type);

		/// <exclude/>
		MMOItemVariable(string name, boost::shared_ptr<long int> val);
		MMOItemVariable(string name, boost::shared_ptr<unsigned long int> val);
		MMOItemVariable(string name, boost::shared_ptr<int> val);
		MMOItemVariable(string name, boost::shared_ptr<unsigned int> val);
		MMOItemVariable(string name, boost::shared_ptr<bool> val);
		MMOItemVariable(string name, boost::shared_ptr<double> val);
		MMOItemVariable(string name, boost::shared_ptr<string> val);
		MMOItemVariable(string name, boost::shared_ptr<SFSObject> val);
		MMOItemVariable(string name, boost::shared_ptr<SFSArray> val);

		virtual ~MMOItemVariable();

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

		/// <summary>
		/// Returns a string that contains the MMOItem Variable name, type and value.
		/// </summary>
		/// 
		/// <returns>
		/// The string representation of the <see cref="Sfs2X.Entities.Variables.MMOItemVariable"/> object.
		/// </returns>
		boost::shared_ptr<string> ToString();

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

	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
