#include <ft_ssl_md5.h>
#include <utils/endian.h>

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

int get_blocks(t_u8_array input, uint8_t **blocks, size_t *block_nb, int block_endian, size_t len_bit_nb) {
	size_t	len_bytes_nb = (len_bit_nb + 7) / 8;
	*block_nb = (input.size + MIN_PADDING_SIZE + len_bytes_nb - 1) / BLOCK_SIZE + 1;
	*blocks = ft_calloc(*block_nb, 64);
	if (*blocks == NULL)
		return (1);
	ft_memcpy(*blocks, input.content, input.size);

	(*blocks)[input.size] = 0x80;

	DBG("Len bytes nb: %d\n", len_bytes_nb);
	uint64_t	len = input.size * 8;
	SWAP_ENDIAN(block_endian, len, 8);
	*((uint64_t *) ((*blocks) + *block_nb * BLOCK_SIZE - len_bytes_nb)) = len;
	return (0);
}