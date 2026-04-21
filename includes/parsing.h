#ifndef PARSING_H
#define PARSING_H

#include <stddef.h>
#include <stdint.h>

#include <utils/log.h>
#include <libft.h>


#define USAGE(program_name) ERR("Usage: %s <command> [flags] [file/string]\n", program_name)

// ---------------------- COMMANDS -------------------

void	md5_handler(void);
void	sha256_handler(void);

#define COMMAND_NB 2
#define COMMANDS { \
	(t_command) {"md5", md5_handler}, \
	(t_command) {"sha256", sha256_handler} \
}

typedef struct s_command
{
	char	*name;
	void	(*hash_algorithm)(void);
}	t_command;

// --------------------- FLAGS ----------------------

#define FLAG_NB 4
#define FLAGS { \
	(t_flag) {'p', ECHO_STDIN_OPT}, \
	(t_flag) {'q', QUIET_OPT}, \
	(t_flag) {'r', REVERSE_OPT}, \
	(t_flag) {'s', 0} \
}

#define ECHO_STDIN_OPT	1
#define QUIET_OPT 		2
#define REVERSE_OPT		4

typedef struct s_flag
{
	char	name;
	uint8_t	mask;
}	t_flag;

// --------------------- STDIN ----------------------

#define	MAX_READ	4096
#define	MAX_STRING	32
#define	MAX_FILES 	32

typedef struct s_stdin
{
	uint8_t	*input;
	size_t	input_size;
} t_stdin;

typedef struct s_params
{
	uint8_t	options;
	char 	*strings[MAX_STRING];
	size_t	string_nb;
	char 	*files[MAX_FILES];
	size_t	file_nb;
	t_stdin	stdin;
	void	(*hash_algorithm)(void);
} t_params;

// --------------------------------------------------

int	parse_args(int argc, char *argv[], t_params *params);


// ---- DBG

void	dbg_show_flags(t_params *params);
void	dbg_show_strings(t_params *params);
void	dbg_show_files(t_params *params);

#endif
