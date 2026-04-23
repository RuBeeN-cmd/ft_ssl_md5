#include <ft_ssl_md5.h>

int	process_hash(t_command *command, t_u8_array input, t_u8_array *output) {
	if (input.content == NULL || input.size == 0)
		return (0);
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
	t_u8_array	stdin;
	if (read_fd(0, &stdin.content, &stdin.size)) {
		return (1);
	}
	if (!stdin.size) {
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
			print_stdin_litteral_inline(stdin);
		}
	}
	if (options & QUIET_OPT) {
		print_hash(hash, 1);
	} else {
		print_hash(hash, 0);
	}

	if (hash.content)
		free(hash.content);
	if (stdin.content)
		free(stdin.content);
	return (0);
}

int	process_strings(int options, t_command *command, char **strings, size_t string_nb) {
	(void) options;
	for (size_t i = 0; i < string_nb; i++) {
		t_u8_array input = {(uint8_t *) strings[i], ft_strlen(strings[i])};
		t_u8_array hash;
		if (process_hash(command, input, &hash))
			return (1);

		if (!(options & QUIET_OPT)) {
			print_cmd_string_inline(command->name, strings[i]);
		}
		if (options & QUIET_OPT) {
			print_hash(hash, 1);
		} else {
			print_hash(hash, 0);
		}

		if (options & REVERSE_OPT) {
			print_suffix_string(strings[i]);
		}

		if (hash.content)
			free(hash.content);
	}
	return (0);
}

int	process_files(int options, t_command *command, char **files, size_t file_nb) {
	for (size_t i = 0; i < file_nb; i++) {
		int fd = open(files[i], O_RDONLY);
		if (fd == -1) {
			ERR("ft_ssl: %s: %s: No such file or directory\n", command->name, files[i]);
			continue;
		}
		t_u8_array	file;
		if (read_fd(fd, &file.content, &file.size)) {
			close(fd);
			ERR("ft_ssl: Error: failed to read file %s\n", files[i]);
			continue;
		}
		close(fd);
		DBG("Ret %d bytes from file %s\n", file.size, files[i]);

		t_u8_array hash;
		if (process_hash(command, file, &hash)) {
			free(file.content);
			continue;
		}

		if (!(options & QUIET_OPT)) {
			print_cmd_file_inline(command->name, files[i]);
		}
		if (options & QUIET_OPT) {
			print_hash(hash, 1);
		} else {
			print_hash(hash, 0);
		}

		// if (options & REVERSE_OPT) {
		// 	print_suffix_string(strings[i]);
		// }

		if (hash.content)
			free(hash.content);

		if (file.content)
			free(file.content);
	}
	return (0);
}

int	process_params(t_params *params) {
	if (params->options & ECHO_STDIN_OPT || (!params->string_nb && !params->file_nb)) {
		if (process_stdin(params->options, &params->hash_command)) {
			return (1);
		}
	}
	if (process_strings(params->options, &params->hash_command, params->strings, params->string_nb)) {
		return (1);
	}
	if (process_files(params->options, &params->hash_command, params->files, params->file_nb)) {
		return (1);
	}
	return (0);
}