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
// void	print_hash(t_u8_array hash, int prefix);
// void	print_stdin_name(t_u8_array stdin);
// void	print_name(char *name, int prefix, int quotes);
// void	print_command(char *command);

void	print_stdin_alone(t_u8_array stdin);
void	print_stdin_inline(t_u8_array stdin);
void	print_stdin_litteral_inline();
void	print_cmd_string_inline(char *cmd, char *string);
void	print_cmd_file_inline(char *cmd, char *file);
void	print_hash(t_u8_array hash, int prefix);
void	print_suffix_string(char *string);
void	print_suffix_file(char *file);

#endif