#include <algorithms/common.h>

int	copy_hash(uint8_t **output, size_t *output_size, uint8_t *input, size_t input_size)
{
	if (!output || !output_size || !input || input_size == 0)
		return (1);
	if (!(*output = malloc(input_size)))
		return (1);
	ft_memcpy(*output, input, input_size);
	*output_size = input_size;
	return (0);
}
