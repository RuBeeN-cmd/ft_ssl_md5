#include <parsing.h>

int parse_command(char *cmd, t_command *command) {
	t_command commands[COMMAND_NB] = COMMANDS;

	for (size_t i = 0; i < COMMAND_NB; i++) {
		if (ft_strncmp(cmd, commands[i].name, ft_strlen(commands[i].name)) == 0) {
			*command = commands[i];
			return (0);
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
	return (1);
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

void	parse_env(char *env[])
{
	for (size_t i = 0; env[i] != NULL; i++) {
		if (ft_strncmp(env[i], "NOPREFIX", 8) == 0) {
			disable_prefix();
		} else if (ft_strncmp(env[i], "NOCOLOR", 7) == 0) {
			disable_colors();
		} else if (ft_strncmp(env[i], "LOGLEVEL", 8) == 0) {
			char *value = ft_strchr(env[i], '=');
			if (value != NULL) {
				*value = '\0';
				value++;
				if (!ft_strncmp(value, "debug", 5))
					set_log_level(LEVEL_DEBUG);
				else if (!ft_strncmp(value, "info", 4))
					set_log_level(LEVEL_INFO);
				else if (!ft_strncmp(value, "warning", 7))
					set_log_level(LEVEL_WARNING);
				else if (!ft_strncmp(value, "error", 5))
					set_log_level(LEVEL_ERROR);
				else {
					int log_level = ft_atoi(value);
					if (log_level >= LEVEL_DEBUG && log_level <= LEVEL_ERROR)
						set_log_level(log_level);
				}
			}
		}
	}
}

int	get_command_from_stdin(t_command *command)
{
	char buf[64] = {};

	int invalid_command = 1;
	t_command cmd = {};

	while (invalid_command == 1) {
		INFO("%s> ", "ft_ssl");
		int ret = read(0, buf, 64);
		if (ret > 0) {
			buf[ret] = 0;
		} else {
			LOG(0, LEVEL_INFO, "\n");
			return (1);
		}
		invalid_command = parse_command(buf, &cmd);
	}
	*command = cmd;
	return (0);
}

int	parse_args(int argc, char *argv[], char *env[], t_params *params)
{
	parse_env(env);


	argc -= 1;
	argv += 1;
	if (argc == 0) {
		int ret = get_command_from_stdin(&params->hash_command);
		if (ret != 0)
			return (1);
	} else if (parse_command(argv[0], &params->hash_command) != 0) {
		return (-1);
	}
	DBG("Running command "ANSI_GREEN"%s"ANSI_RESET"\n", params->hash_command.name);

	argc -= 1;
	argv += 1;
	if (argc <= 0)
		goto exit;

	int ret = parse_flags(argc, argv, params);
	if (ret == -1)
		return (-1);

	argc -= ret;
	argv += ret;
	if (argc <= 0)
		goto exit;

	if (parse_files(argc, argv, params))
		return (-1);

	exit:
		dbg_show_flags(params);
		dbg_show_strings(params);
		dbg_show_files(params);
	return (0);
}