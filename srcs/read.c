#include <ft_ssl_md5.h>

int	read_fd(int fd, uint8_t **result, size_t *size)
{
	int		ret = 0;
	uint8_t	buffer[MAX_READ] = {};
	
	uint32_t	content_size = 0;
	uint8_t		*content = NULL;

	uint8_t		*tmp = NULL;

	while ((ret = read(fd, buffer, MAX_READ)) != 0) {
		tmp = malloc(sizeof(uint8_t) * (content_size + ret));
		if (!tmp) {
			if (content)
				free(content);
			return (1);
		}
		ft_memcpy(tmp, content, content_size);
		ft_memcpy(tmp + content_size, buffer, ret);
		content_size += ret;
		free(content);
		content = tmp;
	}
	if (ret == -1) {
		if (content)
			free(content);
		return 1;
	}
	*result = content;
	*size = content_size;
	return 0;
}