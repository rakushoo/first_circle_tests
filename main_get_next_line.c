#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int     fd;
	char	*p;
	int     rc;

	if (argc == 1)//標準入力
	{
		fd = 0;
	}
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			printf("ファイルオープンエラー\n");
			return (0);
		}
	}
	else
		return (1);

	while (-1/*GNL_ERR*/ != (rc = get_next_line(fd, &p)))
	{
		if (rc == 1/*GNL_READ*/)
		{
			printf("%s\n", p);
			free(p);
			p = NULL;
		}
		else if (rc == 0/*GNL_EOF*/)
		{
			printf("%s", p);
			free(p);
			break ;
		}
	}
	if (rc == -1/*GNL_ERR*/)
	{
		printf("ファイル読み込みエラー\n");
	}
	close(fd);
	return (0);
}
