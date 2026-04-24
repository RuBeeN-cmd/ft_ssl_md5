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

void	ft_strtoupper(char *str, char *upper_str, size_t string_size) {
	if (!str || !upper_str || string_size == 0)
		return ;
	for (size_t i = 0; str[i] && i < string_size - 1; i++) {
		upper_str[i] = ft_toupper(str[i]);
	}
	size_t	len = ft_strlen(str);
	if (len < string_size - 1)
		upper_str[len] = '\0';
	else
		upper_str[string_size - 1] = '\0';
}

// ------------------------------------------------

void	print_stdin_alone(t_u8_array stdin) {
	if (stdin.size && stdin.content[stdin.size - 1] == '\n') {
		stdin.content[stdin.size - 1] = '\0';
		stdin.size--;
	}
	INFO("%s", get_color(COLOR_CYAN));
	write(1, stdin.content, stdin.size);
	LOG(0, LEVEL_INFO, "%s\n", get_color(COLOR_RESET));
}

void	print_stdin_inline(t_u8_array stdin) {
	if (stdin.size && stdin.content[stdin.size - 1] == '\n') {
		stdin.content[stdin.size - 1] = '\0';
		stdin.size--;
	}
	INFO("(\"%s", get_color(COLOR_CYAN));
	write(1, stdin.content, stdin.size);
	LOG(0, LEVEL_INFO, "%s\")= ", get_color(COLOR_RESET));
}

void	print_stdin_litteral_inline() {
	INFO("(%sstdin%s)= ", get_color(COLOR_CYAN), get_color(COLOR_RESET));
}

void	print_cmd_inline(char *cmd, char *string, int has_quotes) {
	char	upper_cmd[MAX_CMD_LEN];
	ft_strtoupper(cmd, upper_cmd, sizeof(upper_cmd));

	char	*quotes = has_quotes ? "\"" : "";
	INFO("%s%s%s (%s%s%s%s%s) = ", get_color(COLOR_GREEN), upper_cmd, get_color(COLOR_RESET),
		quotes, get_color(COLOR_CYAN), string, get_color(COLOR_RESET), quotes);
}

void	print_suffix(char *string, int has_quotes) {
	char	*quotes = has_quotes ? "\"" : "";
	LOG(0, LEVEL_INFO, " %s%s%s%s%s\n", quotes, get_color(COLOR_CYAN), string, get_color(COLOR_RESET), quotes);
}



void	print_hash(t_u8_array hash, int prefix, int nl) {
	if (!hash.content || hash.size == 0)
		return;
	char	*hash_str = get_hash_str(hash);
	if (!hash_str)
		return;
	if (prefix)
		INFO("");
	write(1, hash_str, ft_strlen(hash_str));
	if (nl)
		LOG(0, LEVEL_INFO, "\n");
	free(hash_str);
}