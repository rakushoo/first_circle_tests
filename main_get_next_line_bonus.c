#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"


int	main(int argc, char **argv)
{
	int     fd[10];
	int		fd_num;
	char	*p;
	int     rc;

	if (argc < 1)
		return (0);

	fd_num = argc - 1;
	for (int i = 0; i < fd_num; i++)
	{
		fd[i] = open(argv[i+1], O_RDONLY);
		if (fd[i] == -1)
		{
			printf("File Open Error(%s)\n", argv[i+1]);
			return (0);
		}
	}
	fd[fd_num] = 1234;//2にすれば標準入力
	fd_num++;
	while (1)
	{
		for (int i = 0; i < fd_num; i++)
		{
			rc = get_next_line(fd[i], &p);
			if (rc == -1)
			{
				printf("fd[%d]:File Read Error\n", i);
			}
			else if (rc == 1)
			{
				printf("fd[%d]:Read %s\n", i, p);
				free(p);
			}
			else {
				for (int i = 0; i < (argc - 1); i++)
				{
					close(fd[i]);
				}
				return (0);
			}
		}
	}
	return (0);
}
