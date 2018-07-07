// ===================================================================
//
// Description		
//		Contains the implementation of DefaultPacketEncrypter
//
// Revision history
//		Date			Description
//		01-May-2015		First version
//
// ===================================================================
#include "DefaultPacketEncrypter.h"
#include "../Util/CryptoKey.h"
#include <openssl/evp.h>

namespace Sfs2X {
namespace Core {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
DefaultPacketEncrypter::DefaultPacketEncrypter (boost::shared_ptr<BitSwarmClient> bitSwarm)
{
	this->bitSwarm = bitSwarm;
}

// -------------------------------------------------------------------
// Encrypt
// -------------------------------------------------------------------
void DefaultPacketEncrypter::Encrypt(boost::shared_ptr<ByteArray> data)
{
	boost::shared_ptr<Sfs2X::Util::CryptoKey> ck = bitSwarm->CryptoKey();

    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);

    // If data isn't a multiple of 16, the default behavior is to pad with
    // n bytes of value n, where n is the number of padding bytes required
    // to make data a multiple of the block size.  This is PKCS7 padding.
    // The output then will be a multiple of the block size.
	boost::shared_ptr<ByteArray> dataToEncrypt = boost::shared_ptr<ByteArray>(new ByteArray(data->Bytes()));

	boost::shared_ptr<vector<unsigned char> > dataEncrypted = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
    size_t maxOutputLength = dataToEncrypt->Length() + 16 - (dataToEncrypt->Length() % 16);
    dataEncrypted->resize(maxOutputLength);

    // Enc is 1 to encrypt, 0 to decrypt, or -1 (see documentation).
	EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, &(*(ck->Key()->Bytes()->begin())), &(*(ck->IV()->Bytes()->begin())), 1);

    // EVP_CipherUpdate can encrypt all your data at once, or you can do
    // small chunks at a time.
    int actual_size = 0;
    EVP_CipherUpdate(&ctx, &(*dataEncrypted)[0], &actual_size, &(*(dataToEncrypt->Bytes()->begin())), dataToEncrypt->Length());

    // EVP_CipherFinal_ex is what applies the padding.  
    // If your data is a multiple of the block size, you'll get an extra AES block filled with nothing but padding.
    int final_size;
    EVP_CipherFinal_ex(&ctx, &(*dataEncrypted)[actual_size], &final_size);
    actual_size += final_size;

    dataEncrypted->resize(actual_size);

	data->Bytes(dataEncrypted);

	EVP_CIPHER_CTX_cleanup(&ctx);
}
		
// -------------------------------------------------------------------
// Decrypt
// -------------------------------------------------------------------
void DefaultPacketEncrypter::Decrypt(boost::shared_ptr<ByteArray> data)
{
	boost::shared_ptr<Sfs2X::Util::CryptoKey> ck = bitSwarm->CryptoKey();
	
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);

    // If data isn't a multiple of 16, the default behavior is to pad with
    // n bytes of value n, where n is the number of padding bytes required
    // to make data a multiple of the block size.  This is PKCS7 padding.
    // The output then will be a multiple of the block size.
	boost::shared_ptr<ByteArray> dataToDecrypt = boost::shared_ptr<ByteArray>(new ByteArray(data->Bytes()));

	boost::shared_ptr<vector<unsigned char> > dataDecrypted = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
    size_t maxOutputLength = dataToDecrypt->Length();	// + 16 - (dataToDecrypt->Length() % 16);
    dataDecrypted->resize(maxOutputLength);

    // Enc is 1 to encrypt, 0 to decrypt, or -1 (see documentation).
	EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, &(*(ck->Key()->Bytes()->begin())), &(*(ck->IV()->Bytes()->begin())), 0);

    // EVP_CipherUpdate can decrypt all your data at once, or you can do
    // small chunks at a time.
    int actual_size = 0;
    EVP_CipherUpdate(&ctx, &(*dataDecrypted)[0], &actual_size, &(*(dataToDecrypt->Bytes()->begin())), dataToDecrypt->Length());

    // EVP_CipherFinal_ex is what applies the padding.  
    // If your data is a multiple of the block size, you'll get an extra AES block filled with nothing but padding.
    int final_size;
    EVP_CipherFinal_ex(&ctx, &(*dataDecrypted)[actual_size], &final_size);
    actual_size += final_size;

    dataDecrypted->resize(actual_size);

	data->Bytes(dataDecrypted);

	EVP_CIPHER_CTX_cleanup(&ctx);
}

}	// namespace Core
}	// namespace Sfs2X

