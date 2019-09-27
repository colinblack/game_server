/*
 * Rsa.cpp
 *
 *  Created on: 2011-9-27
 *      Author: dada
 */
#include "Common.h"
#include "evp.h"
#include "x509.h"
#include "x509v3.h"
#include "ssl.h"

///TODO: NOT COMPLETE

bool Crypt::RsaSignature(const string &text, const string &key, string &sign,string type)
{
	if(type != "sha256" && type != "sha1")
	{
		return false;
	}

	unsigned char *sig = NULL;
	unsigned char *passphrase = NULL;
	unsigned int len=0;
	EVP_MD_CTX md_ctx;

	EVP_PKEY *pkey;
	BIO *in;
	in = BIO_new_mem_buf((void *)const_cast<char *>(key.c_str()), -1);
	//in = BIO_new(BIO_s_file());
	//BIO_read_filename(in, key.c_str());
	pkey = PEM_read_bio_PrivateKey(in, NULL, 0, passphrase); // generate sign
	BIO_free(in);

	if(pkey == NULL)
	{
		return false;
	}

	len = EVP_PKEY_size(pkey);
	sig = new unsigned char[(len+1)*sizeof(char)];

	if(type == "sha256")
		EVP_SignInit(&md_ctx, EVP_sha256());
	else if(type == "sha1")
		EVP_SignInit(&md_ctx, EVP_sha1());
	EVP_SignUpdate(&md_ctx, text.c_str(), text.size());
	if (!EVP_SignFinal (&md_ctx, sig, &len, pkey))
	{
		delete sig;
		return false;
	}

	sign.clear();
	sign.append((char *)sig, len);
	OPENSSL_free(sig);
	EVP_PKEY_free(pkey);
	return true;
}

bool Crypt::RsaWithSha1Verify(const string &text, const string &key, const string &signature)
{
	RSA *rsa;
	BIO* in = NULL;
	if(text.empty() || signature.empty())
		return false;
	in = BIO_new_mem_buf((void *)const_cast<char *>(key.c_str()), -1);
	//in = BIO_new(BIO_s_file());
	//BIO_read_filename(in, "/data/release/sg17/pi/conf/platform/rsa_public_key.pem");
	if (NULL == in) {
		error_log("BIO_read_filename error.\n");
		return false;
	}
	//将IO中数据以PEM格式读入EVP_PKEY结构中
	rsa = PEM_read_bio_RSAPublicKey(in, NULL, NULL, NULL);

	if (in != NULL)
		BIO_free(in);
	if (rsa == NULL) {
		error_log("PEM_read_bio_RSA_PUBKEY error.\n");
		return false;
	}

	unsigned char sha1[20];
	SHA1((const unsigned char *)const_cast<char *>(text.c_str()), text.size(), sha1);
	if (1 != RSA_verify(NID_sha1, sha1, 20, (const unsigned char *)const_cast<char *>(signature.c_str()), 128, rsa)) {
		RSA_free(rsa);
		error_log("RSA_verify error.\n");
		return false;
	}
	RSA_free(rsa);
	return true;
}

bool Crypt::RsaVerify(const string &text, const string &key, const string &sign,string type)
{/*
	if(type != "sha256" && type != "sha1")
	{
		return false;
	}

	EVP_MD_CTX md_ctx;
	EVP_PKEY *pkey;
	BIO *in;
	X509 *cert = NULL;
	int err;

	//in = BIO_new_mem_buf((void *)const_cast<char *>(key.c_str()), -1);
	in = BIO_new(BIO_s_file());
	BIO_read_filename(in,"/data/release/sg17/pi/conf/platform/rsa_public_key.pem");
	cert = PEM_read_bio_X509(in, NULL, 0, NULL);
	if (cert)
	{
		pkey = (EVP_PKEY *) X509_get_pubkey(cert);
		X509_free(cert);
	}
	else
	{
		pkey = PEM_read_bio_PUBKEY(in, NULL, 0, NULL);
	}
	BIO_free(in);
	if (pkey == NULL)
	{
		return false;
	}
	info_log("next..................");

	if(type == "sha1")
		EVP_VerifyInit(&md_ctx, EVP_sha1());
	else if(type == "sha256")
		EVP_VerifyInit(&md_ctx, EVP_sha256());
	EVP_VerifyUpdate(&md_ctx, text.c_str(), text.size());
	err = EVP_VerifyFinal(&md_ctx, (const unsigned char *)sign.c_str(), sign.size(), pkey);
	EVP_MD_CTX_cleanup(&md_ctx);
	EVP_PKEY_free(pkey);
	return err == 1;
*/
	return false;
}


