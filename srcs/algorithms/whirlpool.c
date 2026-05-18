#include <algorithms/whirlpool.h>

int whirlpool_handler(uint8_t *blocks, size_t block_nb, uint8_t **hash, size_t *hash_size)
{
	(void)blocks;
	(void)block_nb;
	(void)hash;
	(void)hash_size;
	DBG("WHIRLPOOL command executed\n");
	return (0);
}