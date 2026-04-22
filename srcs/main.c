#include <ft_ssl_md5.h>

int main(int argc, char *argv[])
{
	t_params	params = {};

	set_log_level(LEVEL_DEBUG);
	if (parse_args(argc, argv, &params) != 0)
		return (1);

	process_params(&params);

	return (0);
}
