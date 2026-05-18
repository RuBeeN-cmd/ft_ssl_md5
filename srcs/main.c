#include <ft_ssl_md5.h>

int main(int argc, char *argv[], char *env[])
{
	t_params	params = {};

	set_log_level(LEVEL_DEBUG);

	int ret = parse_args(argc, argv, env, &params);
	if (ret < 0)
		return (1);
	if (ret > 0)
		return (0);

	process_params(&params);
	return (0);
}
