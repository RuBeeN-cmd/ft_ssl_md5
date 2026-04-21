#include <ft_ssl_md5.h>

int	process_hash(uint8_t *input, size_t input_size, int endian) {
	if (input == NULL || input_size == 0)
		return (0);
	uint8_t *blocks;
	size_t block_nb;
	if (get_blocks(input, input_size, &blocks, &block_nb, endian) != 0)
		return (1);
	dbg_print_blocks(blocks, block_nb);
	free(blocks);
	return (0);
}

int	process_stdin(int endian) {
	t_input	stdin;
	if (read_fd(0, &stdin.content, &stdin.size)) {
		return (1);
	}
	DBG("Ret %d bytes from stdin\n", stdin.size);
	if (process_hash(stdin.content, stdin.size, endian))
		return (1);
	if (stdin.content)
		free(stdin.content);
	return (0);
}

int	process_strings(char **strings, size_t string_nb, int endian) {
	for (size_t i = 0; i < string_nb; i++) {
		if (process_hash((uint8_t *) strings[i], ft_strlen(strings[i]), endian)) {
			return (1);
		}
	}
	return (0);
}

int	process_files(char **files, size_t file_nb, int endian) {
	for (size_t i = 0; i < file_nb; i++) {
		int fd = open(files[i], O_RDONLY);
		if (fd == -1) {
			ERR("ft_ssl: Error: failed to open file %s\n", files[i]);
			return (1);
		}
		t_input	file;
		if (read_fd(fd, &file.content, &file.size)) {
			close(fd);
			ERR("ft_ssl: Error: failed to read file %s\n", files[i]);
			return (1);
		}
		close(fd);
		DBG("Ret %d bytes from file %s\n", file.size, files[i]);
		if (process_hash(file.content, file.size, endian)) {
			free(file.content);
			return (1);
		}
		if (file.content)
			free(file.content);
	}
	return (0);
}

int	process_params(t_params *params, int endian) {
	if (!params->string_nb && !params->file_nb) {
		if (process_stdin(endian)) {
			return (1);
		}
	}
	if (process_strings(params->strings, params->string_nb, endian)) {
		return (1);
	}
	if (process_files(params->files, params->file_nb, endian)) {
		return (1);
	}
	return (0);
}