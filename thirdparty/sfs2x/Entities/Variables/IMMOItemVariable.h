// ===================================================================
//
// Description		
//		Contains the definition of IMMOItemVariable interface
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __IMMOItemVariable__
#define __IMMOItemVariable__

#include "../../Util/Common.h"
#include "Variable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

	/// <summary>
	/// The IMMOItemVariable interface defines all the public methods and properties that an object representing a SmartFoxServer MMOItem Variable exposes.
	/// </summary>
	/// 
	/// <remarks>
	/// In the SmartFoxServer 2X client API this interface is implemented by the <see cref="MMOItemVariable"/> class. Read the class description for additional informations.
	/// </remarks>
	/// 
	/// <seealso cref="Sfs2X.Entities.Variables.MMOItemVariable"/>
	class DLLImportExport IMMOItemVariable : public Variable
	{
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif

