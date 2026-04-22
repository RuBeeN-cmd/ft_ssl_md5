#ifndef FT_SSL_MD5_H
#define FT_SSL_MD5_H

#include <parsing.h>
#include <utils/log.h>

#include <endian.h>

#define MIN_PADDING_SIZE	1
#define LEN_SIZE			8
#define BLOCK_SIZE			64

// workflow.c
int	process_params(t_params *params);

// read.c
int	read_fd(int fd, uint8_t **result, size_t *size);

// block.c
int		get_blocks(t_u8_array input, uint8_t **blocks, size_t *block_nb, int block_endian);
void	dbg_print_blocks(uint8_t *block, size_t block_nb);

// print.c
void	print_hash(char *name, int options, t_u8_array hash);

#endif