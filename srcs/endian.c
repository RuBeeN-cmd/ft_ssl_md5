#include <ft_ssl_md5.h>

int get_endian()
{
    unsigned int i = 1;
    char *c;

    c = (char *) &i;
	return (*c == 1 ? LITTLE_ENDIAN : BIG_ENDIAN);
}