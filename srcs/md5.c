#include <ft_ssl_md5.h>

#define F(b, c, d) ((b & c) | (~b & d))
#define G(b, c, d) ((b & d) | (c & ~d))
#define H(b, c, d) (b ^ c ^ d)
#define I(b, c, d) (c ^ (b | ~d))

void md5_handler(uint8_t *blocks, size_t block_nb)
{
    INFO("MD5 command executed\n");

    uint32_t r[16] = { 7, 12, 17, 22,
                       5,  9, 14, 20,
                       4, 11, 16, 23,
                       6, 10, 15, 21 };

    uint32_t k[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
    };

    uint32_t h[4] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };

    for (size_t i = 0; i < block_nb; i++)
    {
        uint32_t *m = (uint32_t *)(blocks + i * 64);
		SWAP_ENDIAN_ARRAY(LITTLE_ENDIAN, m, 4, 16);
        uint32_t h1[4] = { h[0], h[1], h[2], h[3] };

        for (size_t j = 0; j < 64; j++)
        {
            uint32_t f, g;
            if (j < 16)
            {
                f = F(h1[1], h1[2], h1[3]);
                g = j;
            }
            else if (j < 32)
            {
                f = G(h1[1], h1[2], h1[3]);
                g = (5 * j + 1) % 16;
            }
            else if (j < 48)
            {
                f = H(h1[1], h1[2], h1[3]);
                g = (3 * j + 5) % 16;
            }
            else
            {
                f = I(h1[1], h1[2], h1[3]);
                g = (7 * j) % 16;
            }

			int r_index = j % 4 + (j / 16) * 4;
            uint32_t temp = h1[3];
            h1[3] = h1[2];
            h1[2] = h1[1];
			h1[1] = h1[0] + f + k[j] + m[g];
            h1[1] = (h1[1] << r[r_index]) | (h1[1] >> (32 - r[r_index]));
            h1[1] += h1[2];
            h1[0] = temp;
        }

        for (size_t j = 0; j < 4; j++)
            h[j] += h1[j];
    }

    for (size_t j = 0; j < 4; j++)
    {
        h[j] = ((h[j] & 0xFF000000) >> 24) |
               ((h[j] & 0x00FF0000) >>  8) |
               ((h[j] & 0x0000FF00) <<  8) |
               ((h[j] & 0x000000FF) << 24);
    }
    INFO("MD5 hash: %x%x%x%x \n", h[0], h[1], h[2], h[3]);
}