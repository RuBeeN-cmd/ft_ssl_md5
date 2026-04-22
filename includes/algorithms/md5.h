#ifndef ALGORITHMS_MD5_H
#define ALGORITHMS_MD5_H

#include <algorithms/common.h>

#define MD5_NAME			"md5"
#define MD5_HASH_SIZE		(4 * sizeof(uint32_t))
#define MD5_BLOCK_ENDIAN	LITTLE_ENDIAN

int md5_handler(uint8_t *blocks, size_t block_nb, uint8_t **hash, size_t *hash_size);

#endif
