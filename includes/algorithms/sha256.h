#ifndef ALGORITHMS_SHA256_H
#define ALGORITHMS_SHA256_H

#include <algorithms/common.h>

#define SHA256_NAME			"sha256"
#define SHA256_HASH_SIZE	(8 * sizeof(uint32_t))
#define SHA256_BLOCK_ENDIAN	BIG_ENDIAN

int sha256_handler(uint8_t *blocks, size_t block_nb, uint8_t **hash, size_t *hash_size);

#endif
