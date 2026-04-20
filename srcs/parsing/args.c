#include <parsing.h>

int	read_stdin(uint8_t **result, size_t *size)
{
	int		ret = 0;
	uint8_t	buffer[MAX_READ] = {};
	
	uint32_t	content_size = 0;
	uint8_t		*content = NULL;

	uint8_t		*tmp = NULL;

	while ((ret = read(0, buffer, MAX_READ)) != 0) {
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

void	(*parse_command(char *cmd))(void) {
	t_command commands[COMMAND_NB] = COMMANDS;

	for (size_t i = 0; i < COMMAND_NB; i++) {
		if (ft_strncmp(cmd, commands[i].name, ft_strlen(commands[i].name)) == 0) {
			return (commands[i].hash_algorithm);
		}
	}
	ERR("ft_ssl: Error: %s is an invalid command.\n", cmd);
	ERR("\n");
	ERR("Commands:\n");
	for (size_t i = 0; i < COMMAND_NB; i++) {
		ERR("%s\n", commands[i].name);
	}
	
	t_flag flags[FLAG_NB] = FLAGS;
	char flags_str[3 * FLAG_NB + 1] = {0};
	for (size_t i = 0; i < FLAG_NB; i++) {
		flags_str[i * 3] = '-';
		flags_str[i * 3 + 1] = flags[i].name;
		flags_str[i * 3 + 2] = ' ';
	}
	ERR("\n");
	ERR("Flags:\n");
	ERR("%s\n", flags_str);
	return (NULL);
}

int	match_flag(char flag)
{
	t_flag flags[FLAG_NB] = FLAGS;
	for (size_t i = 0; i < FLAG_NB; i++) {
		if (flags[i].name == flag) {
			return (flags[i].mask);
		}
	}
	return (-1);
}

int	parse_flags(int argc, char *argv[], t_params *params)
{
	int i = 0;
	while (i < argc && argv[i][0] == '-')
	{
		if (ft_strlen(argv[i] + 1) > 1) {
			ERR("ft_ssl: Error: invalid flag %s\n", argv[i]);
			return (-1);
		}
		int flag_mask = match_flag(argv[i][1]);
		if (flag_mask == -1) {
			ERR("ft_ssl: Error: invalid flag %s\n", argv[i]);
			return (-1);
		}
		if (argv[i][1] == 's') {
			if (i + 1 >= argc) {
				ERR("ft_ssl: Error: -s flag requires a string argument\n");
				return (-1);
			}
			if (params->string_nb < MAX_STRING) {
				params->strings[params->string_nb++] = argv[i + 1];
			} else {
				ERR("ft_ssl: Error: too many strings\n");
				return (-1);
			}
			i++;
		} else {
			params->options |= flag_mask;
		}
		i++;
	}
	return (i);
}

int	parse_files(int argc, char *argv[], t_params *params)
{
	for (int i = 0; i < argc; i++) {
		if (params->file_nb < MAX_FILES) {
			params->files[params->file_nb++] = argv[i];
		} else {
			ERR("ft_ssl: Error: too many files\n");
			return (1);
		}
	}
	return (0);
}

int	parse_args(int argc, char *argv[], t_params *params)
{
	DBG("Parsing arguments\n");
	if (argc == 1) {
		USAGE(argv[0]);
		return (1);
	}

	params->hash_algorithm = parse_command(argv[1]);
	if (!params->hash_algorithm)
		return (1);

	DBG("Running command "ANSI_GREEN"%s"ANSI_RESET"\n", argv[1]);

	argc -= 2;
	argv += 2;
	int ret = 0;
	if (argc > 0) {
		ret = parse_flags(argc, argv, params);
		if (ret == -1)
			return (1);
	}

	argc -= ret;
	argv += ret;
	if (argc > 0) {
		if (parse_files(argc, argv, params)) {
			return (1);
		}
	}

	dbg_show_flags(params);
	dbg_show_strings(params);
	dbg_show_files(params);

	if (!params->string_nb && !params->file_nb) {
		if (read_stdin(&params->stdin.input, &params->stdin.input_size)) {
			return (1);
		}
		DBG("Ret %d bytes from stdin\n", params->stdin.input_size);
	}
	return (0);
}