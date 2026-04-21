#ifndef FT_SSL_MD5_H
#define FT_SSL_MD5_H

#include <parsing.h>
#include <utils/log.h>

#define MIN_PADDING_SIZE	1
#define LEN_SIZE			8
#define BLOCK_SIZE			64

// block.c
int	process_hashes(t_params *params);

#endif