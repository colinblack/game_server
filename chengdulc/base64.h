
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef BASE64_H
#define BASE64_H

enum base64_result
{
	CRYPT_OK,
	CRYPT_BUFFER_OVERFLOW = 6,
	CRYPT_INVALID_PACKET
};

int base64_encode(const unsigned char *in,  int len, unsigned char *out, int *outlen);
int base64_decode(const unsigned char *in,  int len, unsigned char *out, int *outlen);


#endif
