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
int		get_blocks(t_input input, uint8_t **blocks, size_t *block_nb, int block_endian);
void	dbg_print_blocks(uint8_t *block, size_t block_nb);



// ------------------ Endian ------------------

int get_endian(void);

#define SWAP_ENDIAN(_endian_, _data_, _size_) \
	do { \
		int _crt_endian_ = get_endian(); \
		if (_crt_endian_ != (_endian_)) { \
			switch (_size_) \
			{ \
			case 2: \
				_data_ = __builtin_bswap16(_data_); \
				break; \
			case 4: \
				_data_ = __builtin_bswap32(_data_); \
				break; \
			case 8: \
				_data_ = __builtin_bswap64(_data_); \
				break; \
			default: \
				break; \
			} \
		} \
	} while (0)

#define SWAP_ENDIAN_ARRAY(_endian_, _data_, _size_, _nmenb_) \
	for (size_t _i_= 0; _i_ < _nmenb_; _i_++) \
	{ \
		SWAP_ENDIAN(_endian_, _data_[_i_], _size_); \
	}

#endif

// --------------------------------------------