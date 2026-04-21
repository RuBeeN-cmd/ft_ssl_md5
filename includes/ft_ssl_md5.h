#ifndef FT_SSL_MD5_H
#define FT_SSL_MD5_H

#include <parsing.h>
#include <utils/log.h>

#include <endian.h>

#define MIN_PADDING_SIZE	1
#define LEN_SIZE			8
#define BLOCK_SIZE			64

// workflow.c
int	process_params(t_params *params, int endian);

// read.c
int	read_fd(int fd, uint8_t **result, size_t *size);

// block.c
int		get_blocks(uint8_t *input, size_t input_size, uint8_t **blocks, size_t *block_nb, int endian);
void	dbg_print_blocks(uint8_t *block, size_t block_nb);

// endian.c
int get_endian(void);

#endif