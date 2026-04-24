#include <ft_ssl_md5.h>

int	process_hash(t_command *command, t_u8_array input, t_u8_array *output) {
	uint8_t *blocks;
	size_t block_nb;
	if (get_blocks(input, &blocks, &block_nb, command->block_endian) != 0)
		return (1);
	dbg_print_blocks(blocks, block_nb);

	if (command->hash_algorithm(blocks, block_nb, &output->content, &output->size)) {
		free(blocks);
		return (1);
	}
	free(blocks);
	return (0);
}

int	process_stdin(int options, t_command *command) {
	t_u8_array	stdin = { 0 };
	if (read_fd(0, &stdin.content, &stdin.size)) {
		return (1);
	}
	DBG("Ret %d bytes from stdin\n", stdin.size);

	t_u8_array hash;
	if (process_hash(command, stdin, &hash))
		return (1);
	if (options & ECHO_STDIN_OPT) {
		if (options & QUIET_OPT) {
			print_stdin_alone(stdin);
		} else {
			print_stdin_inline(stdin);
		}
	} else {
		if (!(options & QUIET_OPT)) {
			print_stdin_litteral_inline();
		}
	}
	print_hash(hash, (options & QUIET_OPT) > 0, 1);
	if (hash.content)
		free(hash.content);

	if (stdin.content)
		free(stdin.content);
	return (0);
}

int	process_string(char *string, t_command *command, int options) {
	t_u8_array input = {(uint8_t *) string, ft_strlen(string)};

	t_u8_array hash;
	if (process_hash(command, input, &hash))
		return (1);
	if (!(options & REVERSE_OPT) && !(options & QUIET_OPT)) {
		print_cmd_inline(command->name, string, 1);
	}
	print_hash(hash, (options & QUIET_OPT) > 0 || (options & REVERSE_OPT) > 0, (options & REVERSE_OPT) == 0 || (options & QUIET_OPT) > 0);
	if (options & REVERSE_OPT && !(options & QUIET_OPT)) {
		print_suffix(string, 1);
	}

	if (hash.content)
		free(hash.content);
	return (0);
}

void	process_strings(int options, t_command *command, char **strings, size_t string_nb) {
	for (size_t i = 0; i < string_nb; i++) {
		if (process_string(strings[i], command, options)) {
			continue;
		}
	}
}

int process_file(char *filename, t_command *command, int options) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		ERR("ft_ssl: %s: %s: No such file or directory\n", command->name, filename);
		return (1);
	}
	t_u8_array	file;
	if (read_fd(fd, &file.content, &file.size)) {
		close(fd);
		ERR("ft_ssl: Error: failed to read file %s\n", filename);
		return (1);
	}
	close(fd);
	DBG("Ret %d bytes from file %s\n", file.size, filename);

	t_u8_array hash;
	if (process_hash(command, file, &hash)) {
		free(file.content);
		return (1);
	}
	if (!(options & REVERSE_OPT) && !(options & QUIET_OPT)) {
		print_cmd_inline(command->name, filename, 0);
	}
	print_hash(hash, (options & QUIET_OPT) > 0 || (options & REVERSE_OPT) > 0, (options & REVERSE_OPT) == 0 || (options & QUIET_OPT) > 0);
	if (options & REVERSE_OPT && !(options & QUIET_OPT)) {
		print_suffix(filename, 0);
	}
	if (hash.content)
		free(hash.content);

	if (file.content)
		free(file.content);
	return (0);
}

void	process_files(int options, t_command *command, char **files, size_t file_nb) {
	for (size_t i = 0; i < file_nb; i++) {
		if (process_file(files[i], command, options)) {
			continue;
		}
	}
}

void	process_params(t_params *params) {
	if (params->options & ECHO_STDIN_OPT || (!params->string_nb && !params->file_nb)) {
		process_stdin(params->options, &params->hash_command);
	}
	process_strings(params->options, &params->hash_command, params->strings, params->string_nb);
	process_files(params->options, &params->hash_command, params->files, params->file_nb);
}