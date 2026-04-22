#ifndef UTILS_U8_ARRAY_H
#define UTILS_U8_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct s_u8_array
{
	uint8_t	*content;
	size_t	size;
} t_u8_array;

#endif
