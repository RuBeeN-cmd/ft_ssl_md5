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

int get_blocks(uint8_t *input, size_t input_size, uint8_t **blocks, size_t *block_nb) {
	if (input == NULL || input_size == 0)
		return (1);
	
	*block_nb = (input_size + MIN_PADDING_SIZE + LEN_SIZE - 1) / BLOCK_SIZE + 1;
	*blocks = ft_calloc(*block_nb, 64);

	ft_memcpy(*blocks, input, input_size);

	(*blocks)[input_size] = 0x80;
	*((uint64_t *) ((*blocks) + *block_nb * BLOCK_SIZE - LEN_SIZE)) = input_size;
	return (0);
}

int	process_hash(uint8_t *input, size_t input_size) {
	if (input == NULL || input_size == 0)
		return (1);
	uint8_t *blocks;
	size_t block_nb;
	if (get_blocks(input, input_size, &blocks, &block_nb) != 0)
		return (1);
	dbg_print_blocks(blocks, block_nb);
	free(blocks);
	return (0);
}

int	process_hashes(t_params *params) {
	for (size_t i = 0; i < params->string_nb; i++) {
		process_hash((uint8_t *) params->strings[i], ft_strlen(params->strings[i]));
	}
	return (0);
}