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

void	print_stdin_alone(t_u8_array stdin) {
	INFO("%s", get_color(COLOR_CYAN));
	write(1, stdin.content, stdin.size);
	LOG(0, LEVEL_INFO, "%s\n", get_color(COLOR_RESET));
}

void	print_stdin_inline(t_u8_array stdin) {

	if (stdin.content[stdin.size - 1] == '\n') {
		stdin.content[stdin.size - 1] = '\0';
		stdin.size--;
	}
	INFO("(\"%s", get_color(COLOR_CYAN));
	write(1, stdin.content, stdin.size);
	LOG(0, LEVEL_INFO, "%s\")= ", get_color(COLOR_RESET));
}

void	print_stdin_litteral_inline() {
	INFO("(stdin)= ");
}




void	print_cmd_string_inline(char *cmd, char *string) {
	// TODO: UPPER CMD
	INFO("%s%s%s (\"%s%s%s\") = ", get_color(COLOR_GREEN), cmd, get_color(COLOR_RESET),
		get_color(COLOR_CYAN), string, get_color(COLOR_RESET));
}

void	print_suffix_string(char *string) {
	LOG(0, LEVEL_INFO, " \"%s%s%s\"\n", get_color(COLOR_CYAN), string, get_color(COLOR_RESET));
}




void	print_cmd_file_inline(char *cmd, char *file) {
	// TODO: UPPER CMD
	INFO("%s%s%s (%s%s%s) = ", get_color(COLOR_GREEN), cmd, get_color(COLOR_RESET),
		get_color(COLOR_CYAN), file, get_color(COLOR_RESET));
}

void	print_suffix_file(char *file) {
	LOG(0, LEVEL_INFO, " %s%s%s", get_color(COLOR_CYAN), file, get_color(COLOR_RESET));
}



void	print_hash(t_u8_array hash, int prefix) {
	if (!hash.content || hash.size == 0)
		return;
	char	*hash_str = get_hash_str(hash);
	if (!hash_str)
		return;
	if (prefix)
		INFO("");
	write(1, hash_str, ft_strlen(hash_str));
	LOG(0, LEVEL_INFO, "\n");
	free(hash_str);
}