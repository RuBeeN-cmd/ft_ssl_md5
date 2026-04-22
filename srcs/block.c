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

int get_blocks(t_input input, uint8_t **blocks, size_t *block_nb) {
	if (input.content == NULL || input.size == 0)
		return (1);
	*block_nb = (input.size + MIN_PADDING_SIZE + LEN_SIZE - 1) / BLOCK_SIZE + 1;
	*blocks = ft_calloc(*block_nb, 64);
	if (*blocks == NULL)
		return (1);
	ft_memcpy(*blocks, input.content, input.size);

	(*blocks)[input.size] = 0x80;
	uint64_t	len = input.size * 8;
	SWAP_ENDIAN(LITTLE_ENDIAN, len, 8);
	*((uint64_t *) ((*blocks) + *block_nb * BLOCK_SIZE - LEN_SIZE)) = len;
	return (0);
}