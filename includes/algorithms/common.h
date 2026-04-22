#ifndef ALGORITHMS_COMMON_H
#define ALGORITHMS_COMMON_H

#include <utils/log.h>
#include <utils/endian.h>
#include <stddef.h>
#include <stdint.h>

#define ROTLEFT32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROTRIGHT32(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

int	copy_hash(uint8_t **output, size_t *output_size, uint8_t *input, size_t input_size);

#endif
