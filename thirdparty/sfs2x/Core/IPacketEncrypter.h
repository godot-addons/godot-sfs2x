// ===================================================================
//
// Description		
//		Contains the definition of IPacketEncrypter interface
//
// Revision history
//		Date			Description
//		01-May-2015		First version
//
// ===================================================================
#ifndef __IPacketEncrypter__
#define __IPacketEncrypter__

#include "../Util/ByteArray.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {

	// -------------------------------------------------------------------
	// Interface IPacketEncrypter
	// -------------------------------------------------------------------
	class IPacketEncrypter
	{
	public:
		virtual void Encrypt(boost::shared_ptr<ByteArray> data) = 0;
		virtual void Decrypt(boost::shared_ptr<ByteArray> data) = 0;
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
