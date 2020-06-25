#include <stdio.h>
#include <ctype.h> // isXXX,
#include <string.h>	// memset
#include <stdlib.h>

#include "libft.h"

#define JUDGE(name, val)	\
	printf("[%s test]\t", # name); \
	if (name(val) != ft_ ## name(val)) {\
		printf("NG - %s: %d,%d\n", # name, name(val), ft_ ## name(val));\
	}\
	else {\
		printf("OK - %s\n", # name);\
	}
#define JUDGE_LENGTH(name, val)	\
	printf("[%s test]\t", # name); \
	if (name(val) != ft_ ## name(val)) {\
		printf("NG - %s:\t %zd %zd)\n", # name, name(val), ft_ ## name(val));\
	}\
	else {\
		printf("OK - %s\n", # name);\
	}

#define JUDGE_STR(name, std, mine)	\
	printf("[%s test]\t", # name); \
	if (strcmp(std, mine) != 0) { \
		printf("NG - %s:\t %s, %s\n", # name, std, mine); \
	}\
	else {\
		printf("OK - %s\n", # name);\
	}
#define JUDGE_NUM(name, std, mine) \
	if ((std) != (mine)) { \
		printf("NG - %s:\t %zd, %zd\n", # name, (std), (mine)); \
	}\
	else {\
		printf("OK - %s\n", # name);\
	}
#define JUDGE_ADDR(name, std, mine) \
	if ((std) != (mine)) { \
		printf("NG - %s:\t %p, %p\n", # name, (std), (mine)); \
	}\
	else {\
		printf("OK - %s\n", # name);\
	}

void test_memmove(char *str1, int shift, size_t n)
{
	char std[80], mine[80];
	strcpy(std, str1);
	strcpy(mine, str1);
	void *p_std, *p_mine;
	if (0 <= shift) {
		p_std = memmove(std+shift, std, n);
		p_mine = ft_memmove(mine+shift, mine, n);
	}else{
		p_std = memmove(std, std-shift, n);
		p_mine = ft_memmove(mine, mine-shift, n);
	}
	JUDGE_STR(memmove, std, mine);
}
#define JUDGE_MEMMOVE(str1, shift, n) \
	test_memmove(str1, shift, n);

void test_memcmp(char *str, size_t n)
{
	char buf1[] = "\xff\0\0\xaa\0\xde\xffMACOSX\xff";      /* 途中に空文字のある文字列 */
	char buf2[80];
	memcpy(buf2, str, sizeof(buf2));
	int ret_std, ret_mine;
	ret_std = memcmp(buf1, buf2, n);
	ret_mine= ft_memcmp(buf1, buf2, n);
	if (ret_std == ret_mine)
	{
		printf("OK - memcmp\n");
	} else {
		printf("NG - memcmp: 0x%x, 0x%x\n", ret_std, ret_mine);
	}
}
#define JUDGE_MEMCMP(str, n) \
	printf("[memcmp test]\t");	\
	test_memcmp(str, n);


void test_strl(size_t (*std_f)(char *d, const char *s, size_t l),
			size_t (*mine_f)(char *d, const char *s, size_t l),
			char *src, size_t size)
{
	char std[10] = "abcde";
	char mine[10] = "abcde";
	char s[10];
	strcpy(s, src);
	size_t size_std, size_mine;
	size_std = (std_f)(std, src, size);
	size_mine = (mine_f)(mine, src, size);

	if (strcmp(std, mine) != 0) {
		printf("NG - strlxxx string(%s, %s)\t", std, mine);
	} else {
		printf("OK - strlxxx string(%s)\t", std);
	}
	if (size_std != size_mine) {
		printf("NG - strlxxx length:(%zd, %zd)\n", size_std, size_mine);
	}
	else {
		printf("OK - strlxxx length(%zd)\n", size_std);
	}
}
#define JUDGE_STRL(name, src, size)	\
	printf("[%s test]\t", # name); \
	test_strl(name, ft_ ## name, src, size);

void test_strxchr(char *(*std_f)(const char *s, int c),
			char *(*mine_f)(const char *s, int c), int c)
{
	char std[] = "abcd ef\0ghij";
	char mine[] = "abcd ef\0ghij";
	char *p_std, *p_mine;
	p_std = (std_f)(std, c);
	p_mine = (mine_f)(mine, c);
	if (p_std == 0){
		if (p_mine == 0) {
			printf("OK - strxchr (%p)\n", p_mine);
		}else{
			printf("NG - strxchr (%p)\n", p_mine);
		}
	} else {
		if ((p_std - std) != (p_mine - mine)) {
			printf("NG - strxch string(%lx, %lx)\n", (p_std-std), (p_mine-mine));
		} else {
			printf("OK - strxchr string(%lx)\n", (p_std - std));
		}
	}

}
#define JUDGE_STRXCHR(name, c)	\
	printf("[%s test]\t", # name); \
	test_strxchr(name, ft_ ## name, c);

void test_strnstr(const char *big, const char *little, size_t len)
{
	char largestring[20];
	char smallstring[20];
	strcpy(largestring, big);
	strcpy(smallstring, little);
	char *p_std, *p_mine;
	p_std = strnstr(largestring, smallstring, len);
	p_mine = ft_strnstr(largestring, smallstring, len);
	if (p_std == p_mine){
		printf("OK - strnstr (%s)\n", p_mine);
	}else{
		printf("NG - strnstr (%s, %s)\n", p_std, p_mine);
	}
}
#define JUDGE_STRNSTR(big, little, len)	\
	printf("[strnstr test]\t"); \
	test_strnstr(big, little, len);

void test_strncmp(const char *str, size_t len)
{
	char dest[] = "ABCDE";
	int res_std, res_mine;
	res_std = strncmp(dest, str, len);
	res_mine = ft_strncmp(dest, str, len);
	if (res_std == res_mine){
		printf("OK - strncmp (%d)\n", res_mine);
	}else{
		printf("NG - strncmp (%d, %d)\n", res_std, res_mine);
	}
}
#define JUDGE_STRNCMP(str, len)	\
	printf("[strncmp test]\t"); \
	test_strncmp(str, len);




int main(void)
{
	/* memset */
	{
		char std[] = "0123456789";
		char test[] = "0123456789";
		char *s_p, *t_p;
		s_p = memset(std+2, '*', 5);
		t_p = ft_memset(test+2, '*', 5);
		JUDGE_STR(memset, std, test);
	}
	/* bzero */
	{
		char std[] = "0123456789";
		char test[] = "0123456789";
		bzero(std+3, 4);
		ft_bzero(test+3, 4);
		JUDGE_STR(bzero, std, test);
	}
	/* memcpy */
	{
		char std[128] = {1,1,1,1,1,1,1};
		char test[128] = {1,1,1,1,1,1,1};
        char src[] = "ab\0cde";
		memcpy(std, src, 3);
		ft_memcpy(test, src, 3);
		JUDGE_STR(memcpy, std, test);
	}
	/* memccpy */
	{
		char std[30] = "0123456789";
		char test[30] = "0123456789";
		char *p_s, *p_t;
		p_s = memccpy(std, "fugafuga", 'a', 10);
		p_t = ft_memccpy(test, "fugafuga", 'a', 10);
		JUDGE_STR(memccpy, std, test); //文字列のチェック
		if ((p_s-std) != (p_t-test)) //アドレスのチェック
		{
			printf("NG\n");
		}
		// srcが一致しない場合
		p_s = memccpy(std, "hogehoge", 'a', 10);
		p_t = ft_memccpy(test, "hogehoge", 'a', 10);
		JUDGE_STR(memccpy, std, test); //文字列のチェック
		if (p_s != p_t) //アドレスのチェック
		{
			printf("NG %p,%p\n", p_s,p_t);
		}
		// stop-character
		p_s = memccpy(std, "string with\200inside !", 0600, 21);
		p_t = ft_memccpy(test, "string with\200inside !", 0600, 21);
		JUDGE_STR(memccpy, std, test); //文字列のチェック
		if ((p_s-std) != (p_t-test)) //アドレスのチェック
		{
			printf("NG %p,%p\n", p_s,p_t);
		}
		// param null check
		//printf("[memccpy test] %p \n", ft_memccpy(NULL, "fake", 06, 21));
		//printf("[memccpy test] %p \n", ft_memccpy("fake", NULL, 06, 21));
	}
	/* memmove */
	JUDGE_MEMMOVE("abcdefghijklmnopqrstu", 5, 8);
	JUDGE_MEMMOVE("abcdefghijklmnopqrstu", -3, 8);
	JUDGE_MEMMOVE("abcdefghijklmnopqrstu", 0, 8);
	JUDGE_MEMMOVE("abcdefghijklmnopqrstu", 0, 50);

	/* memchr */
	{
		char std[] = "abcdef\0ghij";
		char test[] = "abcdef\0ghij";
		char *p_s;
		char *p_t;
		p_s = memchr(std, 'h', 12);
		p_t = ft_memchr(test, 'h', 12);
		if ((p_s-std) == (p_t-test)){
			printf("[memchr test]\tOK - memchr\n");
		}else{
			printf("[memchr test]\tNG %p,%p\n", p_s,p_t);
		}
	}
	/* memcmp dest="\xff\0\0\xaa\0\xde\xffMACOSX\xff" */
	JUDGE_MEMCMP("\xff\0\0\xaa\0\xde\xffMACOSX\xff", 3);
	JUDGE_MEMCMP("\xff\0\0\xaa\0\xde\xffMACOSX\xfA", 4);
	JUDGE_MEMCMP("\xff\0\0\xaa\0\xde\x00MBS", 10);
	JUDGE_MEMCMP("\xff\xaa\xde\x12WXYZ", 7);

	/* strlen */
	JUDGE_LENGTH(strlen, "hogehoge");
	/* strlcpy dest="abcde"*/
	JUDGE_STRL(strlcpy, "123", 0);
	JUDGE_STRL(strlcpy, "123", 3);
	JUDGE_STRL(strlcpy, "123", 5);
	JUDGE_STRL(strlcpy, "12345", 0);
	JUDGE_STRL(strlcpy, "12345", 5);
	JUDGE_STRL(strlcpy, "12345", 7);
	JUDGE_STRL(strlcpy, "1234567", 0);
	JUDGE_STRL(strlcpy, "1234567", 3);
	JUDGE_STRL(strlcpy, "1234567", 5);
	JUDGE_STRL(strlcpy, "1234567", 7);
	JUDGE_STRL(strlcpy, "1234567", 9);
	/* strlcat dest="abcde"*/
	JUDGE_STRL(strlcat, "123", 0);
	JUDGE_STRL(strlcat, "123", 3);
	JUDGE_STRL(strlcat, "123", 5);
	JUDGE_STRL(strlcat, "123", 7);
	JUDGE_STRL(strlcat, "12345", 0);
	JUDGE_STRL(strlcat, "12345", 5);
	JUDGE_STRL(strlcat, "12345", 7);
	JUDGE_STRL(strlcat, "1234567", 0);
	JUDGE_STRL(strlcat, "1234567", 5);
	JUDGE_STRL(strlcat, "1234567", 7);
	JUDGE_STRL(strlcat, "1234567", 10);

	/* strchr dest="abc def\0ghij"*/
	JUDGE_STRXCHR(strchr, 'c');
	JUDGE_STRXCHR(strchr, 'h');
	JUDGE_STRXCHR(strchr, ' ');
	/* strrchr dest="abcdef\0ghij"*/
	JUDGE_STRXCHR(strrchr, 'i');
	JUDGE_STRXCHR(strrchr, 'd');
	/* strnstr dest="Foo Bar Baz"*/
	JUDGE_STRNSTR("Foo Bar Baz", "Bar", 10);
	JUDGE_STRNSTR("Foo Bar Baz", "Bar", 4);
	JUDGE_STRNSTR("Foo Bar Baz", "Bad", 2);
	JUDGE_STRNSTR("Foo Bar Baz", "Fo", 2);
	JUDGE_STRNSTR("Foo Bar Baz", "", strlen("Foo Bar Baz"));
	JUDGE_STRNSTR("Foo Bar Baz", "", 0);
	JUDGE_STRNSTR("MZIRIBMZIRIBMZE123", "MZIRIBMZIE", 19);
	JUDGE_STRNSTR("AAAAAAAAAAAAA", "AAAAAAAAAAAAA", 14);
	//printf("[strnstr test] %p \n", ft_strnstr(NULL, "fake", 3));
	//printf("[strnstr test] %p \n", ft_strnstr("fake", NULL, 3));

	/* strncmp dest="ABCDE"*/
	JUDGE_STRNCMP("ABD", 2);
	JUDGE_STRNCMP("ABC", 2);
	JUDGE_STRNCMP("AAA", 2);
	JUDGE_STRNCMP("AB", 2);
	JUDGE_STRNCMP("B", 2);
	JUDGE_STRNCMP("B", 0);
	/* atoi */
	JUDGE(atoi, "   123");
	JUDGE(atoi, "-123");
	JUDGE(atoi, "1234567890");
	JUDGE(atoi, "12345678901");
	JUDGE(atoi, "+-18901");
	JUDGE(atoi, "12.34");
	JUDGE(atoi, "abc");
	JUDGE(atoi, "9223372036854775807");
	JUDGE(atoi, "-9223372036854775808");
	JUDGE(atoi, "99999999999999999999999999");
	JUDGE(atoi, "9223372036854775808");
	JUDGE(atoi, "-9223372036854775809");

	JUDGE(isalpha, '@'); JUDGE(isalpha, 'A'); JUDGE(isalpha, '['); JUDGE(isalpha, '`'); JUDGE(isalpha, 'a'); JUDGE(isalpha, '{'); JUDGE(isalpha, 0x80);
	JUDGE(isdigit, '/'); JUDGE(isdigit, '0'); JUDGE(isdigit, '9'); JUDGE(isdigit, ':');
	JUDGE(isalnum, '/'); JUDGE(isalnum, '0'); JUDGE(isalnum, ':'); JUDGE(isalnum, '@'); JUDGE(isalnum, 'A'); JUDGE(isalnum, '['); JUDGE(isalnum, '}'); JUDGE(isalnum, 0x7f);
	JUDGE(isascii, 0x00); JUDGE(isascii, 'a'); JUDGE(isascii, 0x7F); JUDGE(isascii, 0x80);
	JUDGE(isprint, 0x20); JUDGE(isprint, '!'); JUDGE(isprint, '~'); JUDGE(isprint, 0x7F);
	JUDGE(toupper, 'A'); JUDGE(toupper, '`'); JUDGE(toupper, 'a'); JUDGE(toupper, '{');
	JUDGE(tolower, '@'); JUDGE(tolower, 'A'); JUDGE(tolower, 'Z'); JUDGE(tolower, '[');

	return 0;
}
