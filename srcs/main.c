#include <ft_ssl_md5.h>

int main(int argc, char *argv[])
{
	t_params	params = {};

	set_log_level(LEVEL_DEBUG);
	if (parse_args(argc, argv, &params) != 0)
		return (1);

	int endian = get_endian();
	DBG("System is %s Endian\n", endian == LITTLE_ENDIAN ? "Little" : "Big");

	process_params(&params, endian);

	return (0);
}
