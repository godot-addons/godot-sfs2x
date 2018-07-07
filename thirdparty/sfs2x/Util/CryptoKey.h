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
#ifndef __CryptoKey__
#define __CryptoKey__

#include "./Common.h"
#include "./ByteArray.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {
	
	/// <summary>
	/// The encryption key
	/// </summary>
	class CryptoKey
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		CryptoKey(boost::shared_ptr<ByteArray> iv, boost::shared_ptr<ByteArray> key);
		
		boost::shared_ptr<ByteArray> IV();
		boost::shared_ptr<ByteArray> Key();

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
		boost::shared_ptr<ByteArray> iv;
		boost::shared_ptr<ByteArray> key;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
