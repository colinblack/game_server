/*
 * crc_16.cpp
 *
 *  Created on: 2013-8-23
 *      Author: Administrator
 */
#include "crc_16.h"
#include <config.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

unsigned int POLYNOMIAL = 4129;
int crc_arr[] = {0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFC, 0xFFFFFFF8, 0xFFFFFFF0, 0xFFFFFFE0, 0xFFFFFFC0, 0xFFFFFF80, 0xFFFFFF00, 0xFFFFFE00, 0xFFFFFC00, 0xFFFFF800, 0xFFFFF000, 0xFFFFE000, 0xFFFFC000, 0xFFFF8000};
int crc_table[256];

CrcUtil::CrcUtil()
{
	init_table();
}

bool CrcUtil::enCrypt(char* p,unsigned length,unsigned key)
{
	for(int i=0; i<length; i++)
	{
		p[i] ^= ((char*)&key)[i%4];
	}
	return true;
}


bool CrcUtil::deCrypt(char* p,unsigned length,unsigned key)
{
	for(int i=0; i<length; i++)
	{
		p[i] ^= ((char*)&key)[i%4];
	}
	return true;
}

unsigned CrcUtil::crcBitReflect(unsigned arg1, unsigned arg2)
{
	int  local3 = 0;
	int  local4 = 0;
	int  local5 = 0;
	arg2--;
	int  local6 = 0;

	while(local6 <= arg2)
	{
		local5 = arg2 - local6;
		if((arg1 & 1))
		{
			local3 = (local3|(( 1 << local5) & crc_arr[local5]));
		}
		arg1 = ((arg1 >> 1) & 2147483647);
		local6++;
	}
	return local3;
}


unsigned short CrcUtil::update(const char* arg1,int arg1Len)
{
	int  local4 = 0;
	int  local5 = 0;
	int  arg3 = arg1Len;
	int  local6 = 0;

	while(local6 < arg3)
	{
		local5 = ((crcBitReflect(arg1[local6], 8) & 0xFF) ^ ((local4 >> 8) & 0xFFFFFF));
		local5 = (local5 & 0xFF);
		local4 = (crc_table[local5] ^((local4 << 8) & 0xFFFFFF00));
		local6++;
	}
	unsigned xxx =  (( crcBitReflect(local4,16) ^ 0) & 0xFFFF);
	return xxx;
}

void CrcUtil::init_table()
{
	int  local1 = 0;
	int  local3 = 0;
	int  local4 = 0;
	while (local3 < 0x0100)
	{
		local1 = ((local3 << 8) & 0xFFFFFF00);
		local4 = 0;
		while (local4 < 8)
		{
			local1 = (((local1 & 0x8000)) ? (((local1 << 1) & 0xFFFFFFFE) ^ POLYNOMIAL) : ((local1 << 1) & 0xFFFFFFFE));
			local4++;
		}
		crc_table[local3] = local1;
		local3++;
	}
}

/****************************************/

void *
	memxor(void * dest, const void * src, size_t n)
{
	char const *s = (char const *)src;
	char *d = (char *)dest;

	for (; n > 0; n--)
		*d++ ^= *s++;

	return dest;
}

/* Structure to save state of computation between the single steps.  */
struct sha1_ctx
{
	uint32_t A;
	uint32_t B;
	uint32_t C;
	uint32_t D;
	uint32_t E;

	uint32_t total[2];
	uint32_t buflen;
	uint32_t buffer[32];
};

#if USE_UNLOCKED_IO
# include "unlocked-io.h"
#endif

#ifdef WORDS_BIGENDIAN
# define SWAP(n) (n)
#else
# define SWAP(n) \
	(((n) << 24) | (((n) & 0xff00) << 8) | (((n) >> 8) & 0xff00) | ((n) >> 24))
#endif

#define BLOCKSIZE 4096
#if BLOCKSIZE % 64 != 0
# error "invalid BLOCKSIZE"
#endif

void
	sha1_process_block (const void *buffer, size_t len, struct sha1_ctx *ctx);
void
	sha1_process_bytes (const void *buffer, size_t len, struct sha1_ctx *ctx);

/* This array contains the bytes used to pad the buffer to the next
64-byte boundary.  (RFC 1321, 3.1: Step 1)  */
static const unsigned char fillbuf[64] = { 0x80, 0 /* , 0, 0, ...  */ };


/* Take a pointer to a 160 bit block of data (five 32 bit ints) and
initialize it to the start constants of the SHA1 algorithm.  This
must be called before using hash in the call to sha1_hash.  */
void
	sha1_init_ctx (struct sha1_ctx *ctx)
{
	ctx->A = 0x67452301;
	ctx->B = 0xefcdab89;
	ctx->C = 0x98badcfe;
	ctx->D = 0x10325476;
	ctx->E = 0xc3d2e1f0;

	ctx->total[0] = ctx->total[1] = 0;
	ctx->buflen = 0;
}

/* Put result from CTX in first 20 bytes following RESBUF.  The result
must be in little endian byte order.

IMPORTANT: On some systems it is required that RESBUF is correctly
aligned for a 32-bit value.  */
void *
	sha1_read_ctx (const struct sha1_ctx *ctx, void *resbuf)
{
	((uint32_t *) resbuf)[0] = SWAP (ctx->A);
	((uint32_t *) resbuf)[1] = SWAP (ctx->B);
	((uint32_t *) resbuf)[2] = SWAP (ctx->C);
	((uint32_t *) resbuf)[3] = SWAP (ctx->D);
	((uint32_t *) resbuf)[4] = SWAP (ctx->E);

	return resbuf;
}

/* Process the remaining bytes in the internal buffer and the usual
prolog according to the standard and write the result to RESBUF.

IMPORTANT: On some systems it is required that RESBUF is correctly
aligned for a 32-bit value.  */
void *
	sha1_finish_ctx (struct sha1_ctx *ctx, void *resbuf)
{
	/* Take yet unprocessed bytes into account.  */
	uint32_t bytes = ctx->buflen;
	size_t size = (bytes < 56) ? 64 / 4 : 64 * 2 / 4;

	/* Now count remaining bytes.  */
	ctx->total[0] += bytes;
	if (ctx->total[0] < bytes)
		++ctx->total[1];

	/* Put the 64-bit file length in *bits* at the end of the buffer.  */
	ctx->buffer[size - 2] = SWAP ((ctx->total[1] << 3) | (ctx->total[0] >> 29));
	ctx->buffer[size - 1] = SWAP (ctx->total[0] << 3);

	memcpy (&((char *) ctx->buffer)[bytes], fillbuf, (size - 2) * 4 - bytes);

	/* Process last bytes.  */
	sha1_process_block (ctx->buffer, size * 4, ctx);

	return sha1_read_ctx (ctx, resbuf);
}

/* Compute SHA1 message digest for bytes read from STREAM.  The
resulting message digest number will be written into the 16 bytes
beginning at RESBLOCK.  */
int
	sha1_stream (FILE *stream, void *resblock)
{
	struct sha1_ctx ctx;
	char buffer[BLOCKSIZE + 72];
	size_t sum;

	/* Initialize the computation context.  */
	sha1_init_ctx (&ctx);

	/* Iterate over full file contents.  */
	while (1)
	{
		/* We read the file in blocks of BLOCKSIZE bytes.  One call of the
		computation function processes the whole buffer so that with the
		next round of the loop another block can be read.  */
		size_t n;
		sum = 0;

		/* Read block.  Take care for partial reads.  */
		while (1)
		{
			n = fread (buffer + sum, 1, BLOCKSIZE - sum, stream);

			sum += n;

			if (sum == BLOCKSIZE)
				break;

			if (n == 0)
			{
				/* Check for the error flag IFF N == 0, so that we don't
				exit the loop after a partial read due to e.g., EAGAIN
				or EWOULDBLOCK.  */
				if (ferror (stream))
					return 1;
				goto process_partial_block;
			}

			/* We've read at least one byte, so ignore errors.  But always
			check for EOF, since feof may be true even though N > 0.
			Otherwise, we could end up calling fread after EOF.  */
			if (feof (stream))
				goto process_partial_block;
		}

		/* Process buffer with BLOCKSIZE bytes.  Note that
		BLOCKSIZE % 64 == 0
		*/
		sha1_process_block (buffer, BLOCKSIZE, &ctx);
	}

process_partial_block:;

	/* Process any remaining bytes.  */
	if (sum > 0)
		sha1_process_bytes (buffer, sum, &ctx);

	/* Construct result in desired memory.  */
	sha1_finish_ctx (&ctx, resblock);
	return 0;
}

/* Compute SHA1 message digest for LEN bytes beginning at BUFFER.  The
result is always in little endian byte order, so that a byte-wise
output yields to the wanted ASCII representation of the message
digest.  */
void *
	sha1_buffer (const char *buffer, size_t len, void *resblock)
{
	struct sha1_ctx ctx;

	/* Initialize the computation context.  */
	sha1_init_ctx (&ctx);

	/* Process whole buffer but last len % 64 bytes.  */
	sha1_process_bytes (buffer, len, &ctx);

	/* Put result in desired memory area.  */
	return sha1_finish_ctx (&ctx, resblock);
}

void
	sha1_process_bytes (const void *buffer, size_t len, struct sha1_ctx *ctx)
{
	/* When we already have some bits in our internal buffer concatenate
	both inputs first.  */
	if (ctx->buflen != 0)
	{
		size_t left_over = ctx->buflen;
		size_t add = 128 - left_over > len ? len : 128 - left_over;

		memcpy (&((char *) ctx->buffer)[left_over], buffer, add);
		ctx->buflen += add;

		if (ctx->buflen > 64)
		{
			sha1_process_block (ctx->buffer, ctx->buflen & ~63, ctx);

			ctx->buflen &= 63;
			/* The regions in the following copy operation cannot overlap.  */
			memcpy (ctx->buffer,
				&((char *) ctx->buffer)[(left_over + add) & ~63],
				ctx->buflen);
		}

		buffer = (const char *) buffer + add;
		len -= add;
	}

	/* Process available complete blocks.  */
	if (len >= 64)
	{
#if !_STRING_ARCH_unaligned
# define alignof(type) offsetof (struct { char c; type x; }, x)
# define UNALIGNED_P(p) (((size_t) p) % alignof (uint32_t) != 0)
		if (UNALIGNED_P (buffer))
			while (len > 64)
			{
				sha1_process_block (memcpy (ctx->buffer, buffer, 64), 64, ctx);
				buffer = (const char *) buffer + 64;
				len -= 64;
			}
		else
#endif
		{
			sha1_process_block (buffer, len & ~63, ctx);
			buffer = (const char *) buffer + (len & ~63);
			len &= 63;
		}
	}

	/* Move remaining bytes in internal buffer.  */
	if (len > 0)
	{
		size_t left_over = ctx->buflen;

		memcpy (&((char *) ctx->buffer)[left_over], buffer, len);
		left_over += len;
		if (left_over >= 64)
		{
			sha1_process_block (ctx->buffer, 64, ctx);
			left_over -= 64;
			memcpy (ctx->buffer, &ctx->buffer[16], left_over);
		}
		ctx->buflen = left_over;
	}
}

/* --- Code below is the primary difference between md5.c and sha1.c --- */

/* SHA1 round constants */
#define K1 0x5a827999
#define K2 0x6ed9eba1
#define K3 0x8f1bbcdc
#define K4 0xca62c1d6

/* Round functions.  Note that F2 is the same as F4.  */
#define F1(B,C,D) ( D ^ ( B & ( C ^ D ) ) )
#define F2(B,C,D) (B ^ C ^ D)
#define F3(B,C,D) ( ( B & C ) | ( D & ( B | C ) ) )
#define F4(B,C,D) (B ^ C ^ D)

/* Process LEN bytes of BUFFER, accumulating context into CTX.
It is assumed that LEN % 64 == 0.
Most of this code comes from GnuPG's cipher/sha1.c.  */

void
	sha1_process_block (const void *buffer, size_t len, struct sha1_ctx *ctx)
{
	const uint32_t *words = (const uint32_t *)buffer;
	size_t nwords = len / sizeof (uint32_t);
	const uint32_t *endp = words + nwords;
	uint32_t x[16];
	uint32_t a = ctx->A;
	uint32_t b = ctx->B;
	uint32_t c = ctx->C;
	uint32_t d = ctx->D;
	uint32_t e = ctx->E;

	/* First increment the byte count.  RFC 1321 specifies the possible
	length of the file up to 2^64 bits.  Here we only compute the
	number of bytes.  Do a double word increment.  */
	ctx->total[0] += len;
	if (ctx->total[0] < len)
		++ctx->total[1];

#define rol(x, n) (((x) << (n)) | ((uint32_t) (x) >> (32 - (n))))

#define M(I) ( tm =   x[I&0x0f] ^ x[(I-14)&0x0f] \
	^ x[(I-8)&0x0f] ^ x[(I-3)&0x0f] \
	, (x[I&0x0f] = rol(tm, 1)) )

#define R(A,B,C,D,E,F,K,M)  do { E += rol( A, 5 )     \
	+ F( B, C, D )  \
	+ K	      \
	+ M;	      \
	B = rol( B, 30 );    \
	} while(0)

	while (words < endp)
	{
		uint32_t tm;
		int t;
		for (t = 0; t < 16; t++)
		{
			x[t] = SWAP (*words);
			words++;
		}

		R( a, b, c, d, e, F1, K1, x[ 0] );
		R( e, a, b, c, d, F1, K1, x[ 1] );
		R( d, e, a, b, c, F1, K1, x[ 2] );
		R( c, d, e, a, b, F1, K1, x[ 3] );
		R( b, c, d, e, a, F1, K1, x[ 4] );
		R( a, b, c, d, e, F1, K1, x[ 5] );
		R( e, a, b, c, d, F1, K1, x[ 6] );
		R( d, e, a, b, c, F1, K1, x[ 7] );
		R( c, d, e, a, b, F1, K1, x[ 8] );
		R( b, c, d, e, a, F1, K1, x[ 9] );
		R( a, b, c, d, e, F1, K1, x[10] );
		R( e, a, b, c, d, F1, K1, x[11] );
		R( d, e, a, b, c, F1, K1, x[12] );
		R( c, d, e, a, b, F1, K1, x[13] );
		R( b, c, d, e, a, F1, K1, x[14] );
		R( a, b, c, d, e, F1, K1, x[15] );
		R( e, a, b, c, d, F1, K1, M(16) );
		R( d, e, a, b, c, F1, K1, M(17) );
		R( c, d, e, a, b, F1, K1, M(18) );
		R( b, c, d, e, a, F1, K1, M(19) );
		R( a, b, c, d, e, F2, K2, M(20) );
		R( e, a, b, c, d, F2, K2, M(21) );
		R( d, e, a, b, c, F2, K2, M(22) );
		R( c, d, e, a, b, F2, K2, M(23) );
		R( b, c, d, e, a, F2, K2, M(24) );
		R( a, b, c, d, e, F2, K2, M(25) );
		R( e, a, b, c, d, F2, K2, M(26) );
		R( d, e, a, b, c, F2, K2, M(27) );
		R( c, d, e, a, b, F2, K2, M(28) );
		R( b, c, d, e, a, F2, K2, M(29) );
		R( a, b, c, d, e, F2, K2, M(30) );
		R( e, a, b, c, d, F2, K2, M(31) );
		R( d, e, a, b, c, F2, K2, M(32) );
		R( c, d, e, a, b, F2, K2, M(33) );
		R( b, c, d, e, a, F2, K2, M(34) );
		R( a, b, c, d, e, F2, K2, M(35) );
		R( e, a, b, c, d, F2, K2, M(36) );
		R( d, e, a, b, c, F2, K2, M(37) );
		R( c, d, e, a, b, F2, K2, M(38) );
		R( b, c, d, e, a, F2, K2, M(39) );
		R( a, b, c, d, e, F3, K3, M(40) );
		R( e, a, b, c, d, F3, K3, M(41) );
		R( d, e, a, b, c, F3, K3, M(42) );
		R( c, d, e, a, b, F3, K3, M(43) );
		R( b, c, d, e, a, F3, K3, M(44) );
		R( a, b, c, d, e, F3, K3, M(45) );
		R( e, a, b, c, d, F3, K3, M(46) );
		R( d, e, a, b, c, F3, K3, M(47) );
		R( c, d, e, a, b, F3, K3, M(48) );
		R( b, c, d, e, a, F3, K3, M(49) );
		R( a, b, c, d, e, F3, K3, M(50) );
		R( e, a, b, c, d, F3, K3, M(51) );
		R( d, e, a, b, c, F3, K3, M(52) );
		R( c, d, e, a, b, F3, K3, M(53) );
		R( b, c, d, e, a, F3, K3, M(54) );
		R( a, b, c, d, e, F3, K3, M(55) );
		R( e, a, b, c, d, F3, K3, M(56) );
		R( d, e, a, b, c, F3, K3, M(57) );
		R( c, d, e, a, b, F3, K3, M(58) );
		R( b, c, d, e, a, F3, K3, M(59) );
		R( a, b, c, d, e, F4, K4, M(60) );
		R( e, a, b, c, d, F4, K4, M(61) );
		R( d, e, a, b, c, F4, K4, M(62) );
		R( c, d, e, a, b, F4, K4, M(63) );
		R( b, c, d, e, a, F4, K4, M(64) );
		R( a, b, c, d, e, F4, K4, M(65) );
		R( e, a, b, c, d, F4, K4, M(66) );
		R( d, e, a, b, c, F4, K4, M(67) );
		R( c, d, e, a, b, F4, K4, M(68) );
		R( b, c, d, e, a, F4, K4, M(69) );
		R( a, b, c, d, e, F4, K4, M(70) );
		R( e, a, b, c, d, F4, K4, M(71) );
		R( d, e, a, b, c, F4, K4, M(72) );
		R( c, d, e, a, b, F4, K4, M(73) );
		R( b, c, d, e, a, F4, K4, M(74) );
		R( a, b, c, d, e, F4, K4, M(75) );
		R( e, a, b, c, d, F4, K4, M(76) );
		R( d, e, a, b, c, F4, K4, M(77) );
		R( c, d, e, a, b, F4, K4, M(78) );
		R( b, c, d, e, a, F4, K4, M(79) );

		a = ctx->A += a;
		b = ctx->B += b;
		c = ctx->C += c;
		d = ctx->D += d;
		e = ctx->E += e;
	}
}

#define IPAD 0x36
#define OPAD 0x5c

int
	hmac_sha1 (const void *key, size_t keylen,
	const void *in, size_t inlen, void *resbuf)
{
	struct sha1_ctx inner;
	struct sha1_ctx outer;
	char optkeybuf[20];
	char block[64];
	char innerhash[20];

	/* Reduce the key's size, so that it becomes <= 64 bytes large.  */

	if (keylen > 64)
	{
		struct sha1_ctx keyhash;

		sha1_init_ctx (&keyhash);
		sha1_process_bytes (key, keylen, &keyhash);
		sha1_finish_ctx (&keyhash, optkeybuf);

		key = optkeybuf;
		keylen = 20;
	}

	/* Compute INNERHASH from KEY and IN.  */

	sha1_init_ctx (&inner);

	memset (block, IPAD, sizeof (block));
	memxor (block, key, keylen);

	sha1_process_block (block, 64, &inner);
	sha1_process_bytes (in, inlen, &inner);

	sha1_finish_ctx (&inner, innerhash);

	/* Compute result from KEY and INNERHASH.  */

	sha1_init_ctx (&outer);

	memset (block, OPAD, sizeof (block));
	memxor (block, key, keylen);

	sha1_process_block (block, 64, &outer);
	sha1_process_bytes (innerhash, 20, &outer);

	sha1_finish_ctx (&outer, resbuf);

	return 0;
}


string Crypt::Sha1(const string &text)
{
	unsigned char buffer[20];
	sha1_buffer(text.c_str(), text.size(), buffer);
	string result;
	static char s_itox[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	result.resize(40);
	for(int i = 0; i < 20; i++)
	{
		result[i * 2] = s_itox[(buffer[i]) >> 4];
		result[i * 2 + 1] = s_itox[(buffer[i]) & 0x0F];
	}
	result[40] = '\0';
	return result;
}

string Crypt::Sha1Raw(const string &text)
{
	string result;
	result.resize(20);
	sha1_buffer(text.c_str(), text.size(), (unsigned char *)const_cast<char *>(result.c_str()));
	return result;
}

string Crypt::HmacSha1(const string &text, const string &key)
{
	char buffer[20];
	hmac_sha1(key.c_str(), key.size(), text.c_str(), text.size(), buffer);
	string sBuffer;
	sBuffer.append(buffer, sizeof(buffer));
	return sBuffer;
}


char g_Base64EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char g_Base64DecodeTable[] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
     52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
    255, 255, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,
      7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
     19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
    255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
     37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
     49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255
};

bool Crypt::Base64Encode(string &result, const string &text, const char *altChars)
{
	if(altChars != NULL)
	{
		g_Base64EncodeTable[62] = altChars[0];
		g_Base64EncodeTable[63] = altChars[1];
	}
	size_t textSize = text.size();
	size_t resultSize = ((textSize + 2) / 3 * 4);
	result.resize(resultSize);
	size_t ri = 0;
    size_t i;
    size_t textRoundSize = textSize / 3 * 3;
	for(i = 0; i < textRoundSize; i += 3)
	{
		result[ri++] = g_Base64EncodeTable[(text[i] >> 2) & 0x3f];
		result[ri++] = g_Base64EncodeTable[((text[i] << 4) & 0x30) | ((text[i + 1] >> 4) & 0xf)];
		result[ri++] = g_Base64EncodeTable[((text[i + 1] << 2) & 0x3D) | ((text[i + 2] >> 6) & 0x3)];
		result[ri++] = g_Base64EncodeTable[text[i + 2] & 0x3f];
	}
	if(i < textSize)
	{
        char a = text[i];
        char b = ((i + 1) < textSize) ? text[i + 1] : 0;
        result[ri++] = g_Base64EncodeTable[(a >> 2) & 0x3f];
        result[ri++] = g_Base64EncodeTable[((a << 4) & 0x30) | ((b >> 4) & 0xf)];
        result[ri++] = ((i + 1) < textSize) ? g_Base64EncodeTable[(b << 2) & 0x3D] : '=';
        result[ri++] = '=';
	}
	if(altChars != NULL)
	{
		g_Base64EncodeTable[62] = '+';
		g_Base64EncodeTable[63] = '/';
	}
	return true;
}

bool Crypt::Base64EncodeTrim(string &result, const string &text, const char *altChars)
{
	if(!Base64Encode(result, text, altChars))
	{
		return false;
	}
	size_t resultSize = result.size();
	if(resultSize > 0 && result[resultSize - 1] == '=')
	{
		if(resultSize > 1 && result[resultSize - 2] == '=')
		{
			result.resize(resultSize - 2);
		}
		else
		{
			result.resize(resultSize -1);
		}
	}
	return true;
}

bool Crypt::Base64Decode(string &result, const string &text, const char *altChars)
{
	size_t textSize = text.size();
	size_t resultSize = textSize / 4 * 3;
	if(textSize > 0)
	{
		if(textSize % 4 == 0)
		{
			if(text[textSize - 1] == '=')
			{
				resultSize--;
				if(text[textSize - 2] == '=')
				{
					resultSize--;
				}
			}
		}
		else
		{
			resultSize += textSize % 4 - 1;
		}
	}
	result.resize(resultSize);

	if(altChars != NULL)
	{
		g_Base64DecodeTable['+'] = 255;
		g_Base64DecodeTable['/'] = 255;
		g_Base64DecodeTable[(unsigned char)(altChars[0])] = 62;
		g_Base64DecodeTable[(unsigned char)(altChars[1])] = 63;
	}

	bool success = true;
	size_t ti = 0;
	unsigned char curr = 0;
	unsigned char next;
	for(size_t i = 0; i < resultSize; i++)
	{
		next = g_Base64DecodeTable[(unsigned char)(text[ti++])];
		if(next >= 64)
		{
			success = false;
			break;
		}
		size_t n = i % 3;
		if(n == 0)
		{
			curr = next;
			next = g_Base64DecodeTable[(unsigned char)(text[ti++])];
			if(next >= 64)
			{
				success = false;
				break;
			}
			result[i] = (curr << 2) | ((next >> 4) & 0x3);
			curr = next;
		}
		else if(n == 1)
		{
			result[i] = (curr << 4) | ((next >> 2) & 0xf);
			curr = next;
		}
		else
		{
			result[i] = (curr << 6) | next;
		}
	}

	if(altChars != NULL)
	{
		g_Base64DecodeTable[(unsigned char)(altChars[0])] = 255;
		g_Base64DecodeTable[(unsigned char)(altChars[1])] = 255;
		g_Base64DecodeTable['+'] = 62;
		g_Base64DecodeTable['/'] = 63;
	}

	return success;
}

bool Crypt::Base64UrlEncode(string &result, const string &text)
{
	return Base64Encode(result, text, "-_");
}

bool Crypt::Base64UrlEncodeTrim(string &result, const string &text)
{
	return Base64EncodeTrim(result, text, "-_");
}

bool Crypt::Base64UrlDecode(string &result, const string &text)
{
	return Base64Decode(result, text, "-_");
}