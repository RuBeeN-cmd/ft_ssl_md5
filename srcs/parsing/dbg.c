#include <parsing.h>

void	dbg_show_flags(t_params *params)
{
	if (!params->options) {
		DBG(ANSI_RED"No flags"ANSI_RESET" enabled\n");
		return ;
	}
	t_flag	flags[FLAG_NB] = FLAGS;
	DBG("Flags enabled:\n");
	for (size_t i = 0; i < FLAG_NB; i++) {
		if (params->options & (flags[i].mask)) {
			DBG("\t- -%c\n", flags[i].name);
		}
	}
}

void	dbg_show_strings(t_params *params) {
	if (!params->string_nb) {
		DBG(ANSI_RED"No strings"ANSI_RESET" to hash\n");
		return ;
	}
	DBG("Strings to hash:\n");
	for (size_t i = 0; i < params->string_nb; i++) {
		DBG("\t- \"%s\"\n", params->strings[i]);
	}
}

void	dbg_show_files(t_params *params) {
	if (!params->file_nb) {
		DBG(ANSI_RED"No files"ANSI_RESET" to hash\n");
		return ;
	}
	DBG("Files to hash:\n");
	for (size_t i = 0; i < params->file_nb; i++) {
		DBG("\t- \"%s\"\n", params->files[i]);
	}
}