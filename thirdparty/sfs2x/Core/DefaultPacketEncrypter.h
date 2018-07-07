// ===================================================================
//
// Description		
//		Contains the definition of DefaultPacketEncrypter
//
// Revision history
//		Date			Description
//		01-May-2015		First version
//
// ===================================================================
#ifndef __DefaultPacketEncrypter__
#define __DefaultPacketEncrypter__

#include "IPacketEncrypter.h"
#include "../Bitswarm/BitSwarmClient.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Bitswarm;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {
	
	class DefaultPacketEncrypter : public IPacketEncrypter
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		DefaultPacketEncrypter (boost::shared_ptr<BitSwarmClient> bitSwarm);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		void Encrypt(boost::shared_ptr<ByteArray> data);
		void Decrypt(boost::shared_ptr<ByteArray> data);

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
		boost::shared_ptr<BitSwarmClient> bitSwarm;
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
