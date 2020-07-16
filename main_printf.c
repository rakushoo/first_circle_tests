#include <stdio.h>
#include "ft_printf.h"

#define CASE(msg) \
	printf("---[TEST] %s ---\n", # msg);

#define TEST(testcase) \
{	int std, mine; \
	std = printf( #testcase ); printf("\n"); \
	mine = ft_printf( #testcase ); printf("\n"); \
	judge_retval(std, mine); \
}
#define TEST_ARG1(testcase, val1) \
{	int std, mine; \
	std = printf( #testcase , val1); printf("\n"); \
	mine = ft_printf( #testcase , val1); printf("\n"); \
	judge_retval(std, mine); \
}
#define TEST_ARG2(testcase, val1, val2) \
{	int std, mine; \
	std = printf( #testcase , val1, val2); printf("\n"); \
	mine = ft_printf( #testcase , val1, val2); printf("\n"); \
	judge_retval(std, mine); \
}
#define TEST_ARG3(testcase, val1, val2, val3) \
{	int std, mine; \
	std = printf( #testcase , val1, val2, val3); printf("\n"); \
	mine = ft_printf( #testcase , val1, val2, val3); printf("\n"); \
	judge_retval(std, mine); \
}
void	judge_retval(int std, int mine)
{
	if (std != mine)
		printf("[ERROR] ret_val diff(%d,%d)\n", std, mine);
}

#include <stdlib.h>
int	main(void)
{
	char *p;
	int				i = 10;
	unsigned int	ui = 5;

	// Simple Conversion Management cspdiuxX
	CASE(Simply check each conversion without any flags);
	{
		TEST(simply check);
		TEST(no convert%10%);
		TEST(no convert%010%);
	}
	CASE(Try special cases like 0 or smallest int or empty string or null);
	{
		TEST_ARG1(zero c\t%c,0);
		TEST_ARG1(zero d\t\t%d,0);
		TEST_ARG1(zero i\t\t%i,0);
		TEST_ARG1(zero u\t\t%u,0);
		TEST_ARG1(zero x\t\t%x,0);
		TEST_ARG1(zero X\t\t%X,0);
		TEST_ARG1(smallest c\t%c, 0x80);
		TEST_ARG1(smallest d\t%d, 0x80000000);
		TEST_ARG1(smallest i\t%i, 0x80000000);
		TEST_ARG1(smallest u\t%u, 0x80000000);
		TEST_ARG1(smallest x\t%x, 0x80000000);
		TEST_ARG1(smallest X\t%X, 0x80000000);
		TEST_ARG1(empty string s\t%s, "");
		TEST_ARG1(null pointer s\t%s, NULL);
		TEST_ARG1(null pointer p\t%p, NULL);
	}
	CASE(Try with multiple arguments/conversions);
	{
		TEST_ARG2(string+int\t%s+%i, "string", i);
		TEST_ARG2(unsigned+decimal\t%u+%d, ui, i);
		TEST_ARG2(string+stsring\t%s+%s, "string1", "string2");
	}
	CASE(Try the various conversions in the middle of a sentence);
	{
		TEST_ARG3(test%d|%d|%u\t, 22, 33, 44);
		TEST_ARG3(%s|%x|%X\t, "middle", 22, 33);
	}

#if 1
	//Simple Flags Management -0.*
	CASE(Check the 'minimum file width' with values. bigger. equal and smaller than the string);
	{
		TEST_ARG1(%s, "ABCDEFGHI");
		TEST_ARG1(%12s, "ABCDEFGHI");
		TEST_ARG1(%9s, "ABCDEFGHI");
		TEST_ARG1(%6s, "ABCDEFGHI");
		TEST_ARG1(%.12s, "ABCDEFGHI");
		TEST_ARG1(%.9s, "ABCDEFGHI");
		TEST_ARG1(%.6s, "ABCDEFGHI");
		TEST_ARG1(%12.12s, "ABCDEFGHI");
		TEST_ARG1(%9.12s, "ABCDEFGHI");
		TEST_ARG1(%6.12s, "ABCDEFGHI");
		TEST_ARG1(%12.9s, "ABCDEFGHI");
		TEST_ARG1(%9.9s, "ABCDEFGHI");
		TEST_ARG1(%6.9s, "ABCDEFGHI");
		TEST_ARG1(%12.6s, "ABCDEFGHI");
		TEST_ARG1(%9.6s, "ABCDEFGHI");
		TEST_ARG1(%6.6s, "ABCDEFGHI");
		TEST_ARG1(%.s, "ABCDEFGHI");
	}
	CASE(Check s minimum field width with -);
	{
		TEST_ARG1(%-s, "ABCDEFGHI");
		TEST_ARG1(%-12s, "ABCDEFGHI");
		TEST_ARG1(%-9s, "ABCDEFGHI");
		TEST_ARG1(%-6s, "ABCDEFGHI");
		TEST_ARG1(%-.12s, "ABCDEFGHI");
		TEST_ARG1(%-.9s, "ABCDEFGHI");
		TEST_ARG1(%-.6s, "ABCDEFGHI");
		TEST_ARG1(%-12.12s, "ABCDEFGHI");
		TEST_ARG1(%-9.12s, "ABCDEFGHI");
		TEST_ARG1(%-6.12s, "ABCDEFGHI");
		TEST_ARG1(%-12.9s, "ABCDEFGHI");
		TEST_ARG1(%-9.9s, "ABCDEFGHI");
		TEST_ARG1(%-6.9s, "ABCDEFGHI");
		TEST_ARG1(%-12.6s, "ABCDEFGHI");
		TEST_ARG1(%-9.6s, "ABCDEFGHI");
		TEST_ARG1(%-6.6s, "ABCDEFGHI");
		TEST_ARG1(%.-6s, "ABCDEFGHI");
	}
	//Warningが出るが -Wno-format でログ消える
	CASE(Check s minimum field width with 0);
	{
		TEST_ARG1(%0s, "ABCDEFGHI");
		TEST_ARG1(%012s, "ABCDEFGHI");
		TEST_ARG1(%09s, "ABCDEFGHI");
		TEST_ARG1(%06s, "ABCDEFGHI");
		TEST_ARG1(%0.12s, "ABCDEFGHI");
		TEST_ARG1(%0.9s, "ABCDEFGHI");
		TEST_ARG1(%0.6s, "ABCDEFGHI");
		TEST_ARG1(%012.12s, "ABCDEFGHI");
		TEST_ARG1(%09.12s, "ABCDEFGHI");
		TEST_ARG1(%06.12s, "ABCDEFGHI");
		TEST_ARG1(%012.9s, "ABCDEFGHI");
		TEST_ARG1(%09.9s, "ABCDEFGHI");
		TEST_ARG1(%06.9s, "ABCDEFGHI");
		TEST_ARG1(%012.6s, "ABCDEFGHI");
		TEST_ARG1(%09.6s, "ABCDEFGHI");
		TEST_ARG1(%06.6s, "ABCDEFGHI");
	}
	CASE(Check the '.' with multiple precisions);
	{
		TEST_ARG1(%.3.9.12s, "ABCDEFGHI");
		TEST_ARG1(%.3.12.9s, "ABCDEFGHI");
		TEST_ARG1(%.12.9.3s, "ABCDEFGHI");
		TEST_ARG1(%0.3.9.12s, "ABCDEFGHI");
		TEST_ARG1(%0.3.12.9s, "ABCDEFGHI");
		TEST_ARG1(%0.12.9.3s, "ABCDEFGHI");
		TEST_ARG1(%-.3.9.12s, "ABCDEFGHI");
		TEST_ARG1(%.3-.9.12s, "ABCDEFGHI");
		TEST_ARG1(%.3.9-.12s, "ABCDEFGHI");
		TEST_ARG1(%.3.9.12-s, "ABCDEFGHI");
	}
#endif

	//Advanced Flags Management
	CASE(Check '*' as minimum field width. -1 or 0 etc.);
	{
		TEST_ARG2(minimum_field *\t\t%*s, 2,"ABCDE");
		TEST_ARG2(minimum_field *\t\t%*s,-1,"ABCDE"); //NG
		TEST_ARG2(minimum_field *\t\t%*s, 0,"ABCDE");
	}
	CASE(Check '*' as precision. -1 or 0 etc.);
	{
		TEST_ARG2(precision *\t\t%.*s, -4, "ABCDE");
		TEST_ARG2(precision *\t\t%.*s, -3, "ABCDE");
		TEST_ARG2(precision *\t\t%.*s, 0, "ABCDE"); //NG
	}
	CASE(Check '*' as both);
	{
		TEST_ARG3(both *\t\t%0*.*s, -2, -2, "abcde"); //NG
		TEST_ARG3(both *\t\t%0*.*s, -2, 0, "abcde"); //NG
		TEST_ARG3(both *\t\t%0*.*s, -2, 4, "abcde"); //NG
		TEST_ARG3(both *\t\t%0*.*s, -2, 8, "abcde"); //NG
		TEST_ARG3(both *\t\t%0*.*s, 0, -2, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 0, 0, "abcde"); //NG
		TEST_ARG3(both *\t\t%0*.*s, 0, 4, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 0, 8, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 4, -2, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 4, 0, "abcde"); //NG 値と長さ差分
		TEST_ARG3(both *\t\t%0*.*s, 4, 4, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 4, 8, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 8, -2, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 8, 0, "abcde"); //NG 値だけ差分
		TEST_ARG3(both *\t\t%0*.*s, 8, 4, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 8, 8, "abcde");
	}

#if 1
	//Get Crazy
	CASE(XXX!!!***>>>??? Get Crazy ```+++***###$$$);
	{
		TEST(tab_\t_can_show);
		TEST(exc_\\_can_show);
		TEST(question_\?_can_show);
		TEST(percent_%%_can_show);
		TEST_ARG3(astarisc minus\t%.*s%d, -3, "abcde", 888); //精度の時は-値は無視する
		TEST_ARG3(astarisc minus\t%*s%d, -10, "abcde", 888); // -10に置き換えて、左詰

		CASE(d convert);
		TEST_ARG1(%10.3d, 123456789);
		TEST_ARG1(%6.3d, 123456789);
		TEST_ARG1(%6.3d, -123456789);
		TEST_ARG1(%5.12d, 123456789);
		TEST_ARG1(%015.3d, 123456789);
		TEST_ARG1(%-15.12d, 123456789);
		TEST_ARG1(%15.d, 123456789);
		TEST_ARG1(%d, 2147483647);
		TEST_ARG1(%d, -2147483648);

		CASE(Bigger Parameter Case);
		TEST_ARG1(%2147483647s max int wd, "123");// 即error 改行も出力されない
		TEST_ARG1(%2147483648s over int wd, "123");// 即error 改行も出力されない
		TEST_ARG1(%.2147483647s max int precision, "123");
		TEST_ARG1(%.2147483648s over int precision, "123");
		TEST_ARG2(%*s max int wd param, 2147483647, "ABC");// 即error 改行も出力されない
		TEST_ARG2(%*s over int wd param, 2147483648, "ABC");// 即error 改行も出力されない
		TEST_ARG2(%.*s max int precision param, 2147483647, "ABC");
		TEST_ARG2(%.*s over int precision param, 2147483648, "ABC");
		TEST_ARG2(%*s min int wd param, -2147483648, "ABC");
		TEST_ARG2(%.*s min int precision param, -2147483648, "ABC");

		TEST_ARG1(%100.4s, "123456789");
		TEST_ARG1(%-100.4s, "123456789");
		TEST_ARG1(%0100.4s, "123456789");
		TEST_ARG1(%.2147483647s, "123456789");
		TEST_ARG1(%.3000000000s, "123456789");
		TEST_ARG1(%11111111111.4s, "123456789");//Errorになるケース
		TEST_ARG1(%4.111111111111s, "123456789");

		TEST_ARG1(%050.25d, -4000);
		TEST_ARG1(%010.5s, "123456");
		TEST_ARG1(%02147483647.25d, -111); //エラー終了
	}
#endif


	return 0;
}