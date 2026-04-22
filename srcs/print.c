#include <ft_ssl_md5.h>

char	*get_hash_str(t_u8_array hash) {
	char	*str = malloc(hash.size * 2 + 1);
	if (!str)
		return (NULL);
	for (size_t i = 0; i < hash.size; i++) {
		uint8_t byte = hash.content[i];
		str[i * 2] = (byte / 16) + '0';
		if (str[i * 2] > '9')
			str[i * 2] = str[i * 2] - '9' - 1 + 'a';

		str[i * 2 + 1] = (byte % 16) + '0';
		if (str[i * 2 + 1] > '9')
			str[i * 2 + 1] = str[i * 2 + 1] - '9' - 1 + 'a';
	}
	str[hash.size * 2] = '\0';
	return (str);
}

void	print_hash(char *name, int options, t_u8_array hash)
{
	if (!hash.content || hash.size == 0)
		return;
	(void) options;
	(void) name;
	
	INFO("(%s)= ", name);

	char	*hash_str = get_hash_str(hash);
	if (hash_str) {
		LOG(0, LEVEL_INFO, "%s", hash_str);
		free(hash_str);
	}

	LOG(0, LEVEL_INFO, "\n");
}
