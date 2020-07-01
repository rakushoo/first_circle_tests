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

	while (GNL_EOF != (rc = get_next_line(fd, &p)))
	{
		if (rc == GNL_ERR)
		{
			printf("ファイル読み込みエラー\n");
			break ;
		}
		printf("%s\n", p);
		free(p);
		p = NULL;
	}
	close(fd);
	return (0);
}
