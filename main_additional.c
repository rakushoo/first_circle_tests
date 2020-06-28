#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "libft.h"

#define JUDGE_STR(name, std, mine)	\
	printf("[%s test]\t", # name); \
	if (strcmp(std, mine) != 0) { \
		printf("NG:\t%s, %s\n", std, mine); \
	}\
	else {\
		printf("OK:\t%s\n", std);\
	}

void test_substr(const char *str, unsigned int start, size_t len, const char *expected)
{
	char *p_mine = ft_substr(str, start, len);
	JUDGE_STR(substr, expected, p_mine);
	free(p_mine);
}
void test_strjoin(char const *s1, char const *s2)
{
	char std[64];
	strcpy(std, s1);
	strcat(std, s2);
	char *p_mine = ft_strjoin(s1, s2);
	JUDGE_STR(strjoin, std, p_mine);
	free(p_mine);
}
void test_strtrim(char const *s1, char const *set, const char *expected)
{
	char *p_mine = ft_strtrim(s1, set);
	if ((p_mine == NULL) || (*expected==0)){
		JUDGE_STR(strtrim, "(null)", "(null)");
	}else{
		JUDGE_STR(strtrim, expected, p_mine);
		free(p_mine);
	}
}
void test_split(char const *s, char c)
{
	char **pp_top = ft_split(s, c);
	char **pp_mine = pp_top;
	size_t length = strlen(s);
	char *mine = malloc(length + 2);
	while (*pp_mine != NULL) {
		strcat(mine, *pp_mine);
		//strcat(mine, c); //splitされた文字を置き換える
		strcat(mine, " "); //見やすいように_で区切る。必ずNGになる。
		free(*pp_mine);
		pp_mine++;
	}
	printf("[split test]\t%s / %c -> %s\n", s, c, mine);
	free(pp_top);
	free(mine);
}

char	dummy_api(unsigned int n, char c)
{
	(void)n;
	return (ft_toupper(c));
}
void	test_strmapi(char const *s, const char* expected)
{
	char *p_mine = ft_strmapi(s, dummy_api);
	if (p_mine == NULL){
		JUDGE_STR(strmapi, "(null)", "(null)");
	}else{
		JUDGE_STR(strmapi, expected, p_mine);
		free(p_mine);
	}
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define FILE_MODE  (O_WRONLY|O_CREAT|O_TRUNC)
void test_putchar_fd(char c)
{
	//int	fd = open("./test_putchar_fd.txt", FILE_MODE);
	int fd = 2;
	ft_putchar_fd(c, fd);
	//close(fd);
}
void test_putstr_fd(char *s)
{
	//int fd = open("./test_putstr_fd.txt", FILE_MODE);
	int fd = 2;
	ft_putstr_fd(s, fd);
	//close(fd);
}
void test_putendl_fd(char *s)
{
	//int fd = open("./test_putendl_fd.txt", FILE_MODE);
	int fd = 2;
	ft_putendl_fd(s, fd);
	//close(fd);
}
void test_putnbr_fd(int n)
{
	//int fd = open("./test_putnbr_fd.txt", FILE_MODE);
	int fd = 2;
	ft_putnbr_fd(n, fd);
	//close(fd);
}


int main(void)
{
	test_substr("01234567", 3, 4, "3456");
	test_substr("01234567", 3, 10, "34567");
	test_substr("01234567", 10, 10, "");
	test_substr("01234567", 0, 5, "01234");
	test_substr("01234567", 4, 0, "");
	test_substr("01234567", -3, 5, "");
	test_substr("01234567", 3, 0, "");
	test_substr("01234567", 0, -2, "01234567"); //size_tにマイナス値は128以上
	test_substr("", 0, 0, "");
	test_substr(NULL, 0, 0, "");

	test_strjoin("abcd", "EFGHI");
	test_strjoin("", "EFGHI");
	test_strjoin("abcd", "");
	//test_strjoin(NULL, NULL); // segmentation fault

	test_strtrim("aabbccddeeff", "aef", "bbccdd");
	test_strtrim("aabbccddeeff", "z", "aabbccddeeff");
	test_strtrim("aabbccddeeff", "abcdef", "");
	test_strtrim("cccabcdeabcdeccc", "c", "abcdeabcde");
	test_strtrim("  abcd  eab  cde ", " ", "abcd  eab  cde");
	test_strtrim("  \t \t \n   \n\n\n\t", " \n\t", "");
	test_strtrim("   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ", " \n\t", "Hello \t  Please\n Trim me !");
	test_strtrim("aaaaaaaaa", "abcdef", "");
	test_strtrim("", "bcde", "");
	test_strtrim("test", "", "test");

	test_split("0.123,4455.342,ad/11", '.');
	test_split("0.123,4455.342,ad/11", '_');
	test_split("000000000", '0');
	test_split("cabcdeabcdeabcdec", 'c');

	JUDGE_STR(itoa, "12345", ft_itoa(12345));
	JUDGE_STR(itoa, "2147483647", ft_itoa(2147483647));
	JUDGE_STR(itoa, "-2147483648", ft_itoa(-2147483648));
	JUDGE_STR(itoa, "0", ft_itoa(0));
	JUDGE_STR(itoa, "0", ft_itoa(-+-+0000));

	test_strmapi("abcdefg", "ABCDEFG");
	test_strmapi(NULL, "");

	test_putchar_fd('X');
	test_putstr_fd("ABCDE");
	test_putendl_fd("abcde");
	test_putnbr_fd(12345);
	test_putnbr_fd(2147483647);
	test_putnbr_fd(-2147483648);

	return 0;
}
