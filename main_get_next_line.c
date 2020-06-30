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

	while (0 != (rc = get_next_line(fd, &p)))
	{
		if (rc == -1)
		{
			printf("ファイル読み込みエラー\n");
			break ;
		}
		printf("read:%d - %s\n", rc, p);
		free(p);
	}
	close(fd);
	return (0);
}
