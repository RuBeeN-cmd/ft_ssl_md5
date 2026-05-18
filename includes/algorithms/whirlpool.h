#ifndef ALGORITHMS_WHIRLPOOL_H
#define ALGORITHMS_WHIRLPOOL_H

#include <algorithms/common.h>

#define WHIRLPOOL_NAME				"whirlpool"
#define WHIRLPOOL_HASH_SIZE			(8 * sizeof(uint32_t))
#define WHIRLPOOL_BLOCK_LEN_SIZE	(256)
#define WHIRLPOOL_BLOCK_ENDIAN		BIG_ENDIAN

int whirlpool_handler(uint8_t *blocks, size_t block_nb, uint8_t **hash, size_t *hash_size);

#endif