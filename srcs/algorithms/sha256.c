#include <algorithms/sha256.h>

#define SIGMA0(x) (ROTRIGHT32(x, 7) ^ ROTRIGHT32(x, 18) ^ ((x) >> 3))
#define SIGMA1(x) (ROTRIGHT32(x, 17) ^ ROTRIGHT32(x, 19) ^ ((x) >> 10))

#define EP0(x) (ROTRIGHT32(x, 2) ^ ROTRIGHT32(x, 13) ^ ROTRIGHT32(x, 22))
#define EP1(x) (ROTRIGHT32(x, 6) ^ ROTRIGHT32(x, 11) ^ ROTRIGHT32(x, 25))

#define CH(x, y, z) ((x) & (y) ^ (~(x) & (z)))
#define MAJ(x, y, z) ((x) & (y) ^ ((x) & (z) ^ (y) & (z)))

int sha256_handler(uint8_t *blocks, size_t block_nb, uint8_t **hash, size_t *hash_size)
{
	INFO("SHA256 command executed\n");
	if (!hash || !hash_size)
		return (1);

	uint32_t k[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	uint32_t h[8] = {
		0x6a09e667,
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19
	};

    for (size_t i = 0; i < block_nb; i++)
    {
		uint32_t *m = (uint32_t *)(blocks + i * 64);
		SWAP_ENDIAN_ARRAY(SHA256_BLOCK_ENDIAN, m, 4, 16);

		uint32_t W[64] = {0};
		for (size_t j = 0; j < 64; j++)
		{
			if (j < 16)
				W[j] = m[j];
			else
				W[j] = SIGMA1(W[j - 2]) + W[j - 7] + SIGMA0(W[j - 15]) + W[j - 16];
		}

        uint32_t h1[8] = { h[0], h[1], h[2], h[3], h[4], h[5], h[6], h[7] };
		for (size_t j = 0; j < 64; j++)
        {
			uint32_t t1 = h1[7] + EP1(h1[4]) + CH(h1[4], h1[5], h1[6]) + k[j] + W[j];
			uint32_t t2 = EP0(h1[0]) + MAJ(h1[0], h1[1], h1[2]);

			h1[7] = h1[6];
			h1[6] = h1[5];
			h1[5] = h1[4];
			h1[4] = h1[3] + t1;
			h1[3] = h1[2];
			h1[2] = h1[1];
			h1[1] = h1[0];
			h1[0] = t1 + t2;
		}


        for (size_t j = 0; j < 8; j++)
            h[j] += h1[j];
	}
	SWAP_ENDIAN_ARRAY(SHA256_BLOCK_ENDIAN, h, 4, 8);
	if (copy_hash(hash, hash_size, (uint8_t *) h, SHA256_HASH_SIZE))
		return (1);
	return (0);
}