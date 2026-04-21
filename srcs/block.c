#include <ft_ssl_md5.h>

void	dbg_print_blocks(uint8_t *block, size_t block_nb)
{
	DBG("Bloc nb: %d\n", block_nb);
	for (size_t i = 0; i < block_nb * 64; i++)
	{
		if (i % 64 == 0)
			DBG("");
		LOG(0, LEVEL_DEBUG, "%X ", block[i]);
		if (i % 64 == 63)
			LOG(0, LEVEL_DEBUG, "\n");
	}
}

int get_blocks(uint8_t *input, size_t input_size, uint8_t **blocks, size_t *block_nb, int endian) {
	if (input == NULL || input_size == 0)
		return (1);
	(void) endian;
	*block_nb = (input_size + MIN_PADDING_SIZE + LEN_SIZE - 1) / BLOCK_SIZE + 1;
	*blocks = ft_calloc(*block_nb, 64);
	if (*blocks == NULL)
		return (1);
	ft_memcpy(*blocks, input, input_size);

	(*blocks)[input_size] = 0x80;
	if (endian == BIG_ENDIAN)
		input_size = __builtin_bswap64(input_size);
	*((uint64_t *) ((*blocks) + *block_nb * BLOCK_SIZE - LEN_SIZE)) = input_size;
	return (0);
}