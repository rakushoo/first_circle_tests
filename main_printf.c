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
	char c;
#if 0
	//未対応ケース
	TEST_ARG1(%1.3ywqd, 135);
	TEST_ARG1(%12.34qd, 50);
	TEST(%12.34q);
#endif

#if 1
	TEST_ARG1(%020u, (unsigned int)&c);//0x0000007ffee1246787
	TEST_ARG1(%015.3p, &c);	// 0x7ffee45c2777
	TEST_ARG1(%20p, &c);	//      0x7ffee1246787
	TEST_ARG1(%020p, &c);	//0x0000007ffee1246787
	TEST_ARG1(%020.0p, &c);	//      0x7ffee1246787
	TEST_ARG1(%020.p, &c);	//      0x7ffee1246787
	TEST_ARG1(%12.34d, 50);
	TEST_ARG1(%.10d, 12345);//0000012345

	TEST_ARG1(%-14.16p, &c);		//0x00007ffee9e2a777
	TEST_ARG1(%-10.16p, &c);		//0x00007ffee9e2a777
	TEST_ARG1(%-16.14p, &c);		//0x007ffee9e2a777
	TEST_ARG1(%-14.15d, 7654321);	//000000007654321
	TEST_ARG1(%-15.12d, 7654321);	//000007654321
	TEST_ARG1(%014p, &c);			//0x00007ffee9e2a777
	TEST_ARG1(%010p, &c);			//0x00007ffee9e2a777
	TEST_ARG1(%016p, &c);			//0x007ffee9e2a777
#endif

#if 1
	TEST(%-5%);
	TEST(%-05%);
	TEST(%);
	TEST(%-05);
	TEST_ARG1(%.0i, 0);
	TEST_ARG1(%.0x, 0);
	TEST_ARG1(%-5.i, 0);
	TEST_ARG1(%5.d, 0);
	TEST_ARG1(%5.0X, 0);
	TEST_ARG1(%020d, 12345);		//00000000000000012345
	TEST_ARG1(%010d, 1234567);		//0001234567
	TEST_ARG1(%010.d, 0);			//   1234567 0が設定されてフラグ取り消し
	TEST_ARG1(%010.d, 1234567);		//   1234567 0が設定されてフラグ取り消し
	TEST_ARG1(%010.0d, 1234567);	//   1234567 0が設定されてフラグ取り消し
	TEST_ARG2(%010.*d, -5, 1234567);//0001234567
	TEST_ARG1(%0.0d, 123456);

	char s_hidden[] = "hi low";
	TEST_ARG1(%3.1s, s_hidden);
	TEST_ARG1(%3s, s_hidden);
	TEST_ARG1(%-10.1s, s_hidden);
#endif
	TEST_ARG1(%.p, NULL);
	TEST_ARG1(%p, NULL);
	TEST_ARG1(%c, 0);
	TEST_ARG1(%c, -0);
	TEST_ARG1(%5c, '\0');
	TEST_ARG1(%c, 0x0);
	TEST_ARG1(%4.111111111111s, "123456789");
	TEST_ARG2(minimum_field *\t\t%*s, 2,"ABCDE");
#if 1
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
		TEST_ARG3(both *\t\t%0*.*s, -2, -2, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, -2, 0, "abcde"); //NG
		TEST_ARG3(both *\t\t%0*.*s, -2, 4, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, -2, 8, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 0, -2, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 0, 0, "abcde"); //NG
		TEST_ARG3(both *\t\t%0*.*s, 0, 4, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 0, 8, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 4, -2, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 4, 0, "abcde"); //NG 値と長さ差分
		TEST_ARG3(both *\t\t%0*.*s, 4, 4, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 4, 8, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 8, -2, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 8, 0, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 8, 4, "abcde");
		TEST_ARG3(both *\t\t%0*.*s, 8, 8, "abcde");
	}

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
		TEST_ARG1(%d, 12345);
		TEST_ARG1(%20d, 12345);
		TEST_ARG1(%020d, 12345);
		TEST_ARG1(%20-d, 12345);
		TEST_ARG1(%.3d, 12345);
		TEST_ARG1(%.10d, 12345);
		TEST_ARG1(%0.10d, 12345);
		TEST_ARG1(%.20d, -12345);
		TEST_ARG1(%015.3d, 1234567);//0フラグが取り消されるケース
		TEST_ARG1(%-12.15d, 7654321);
		TEST_ARG1(%-15.12d, 7654321);
		TEST_ARG1(%010d, 1234567);
		TEST_ARG1(%010.d, 1234567); //0が設定されてフラグ取り消し
		TEST_ARG1(%010.0d, 1234567); //0が設定されてフラグ取り消し
		TEST_ARG2(%010.*d, -5, 1234567);

		TEST_ARG1(%9d, 123456);
		TEST_ARG1(%-6d, 123456);
		TEST_ARG1(%-9d, 123456);
		TEST_ARG1(%06d, 123456);
		TEST_ARG1(%09d, 123456);
		TEST_ARG1(%0.0d, 123456);
		TEST_ARG1(%3.0d, 123456);
		TEST_ARG1(%6.0d, 123456);
		TEST_ARG1(%9.0d, 123456);
		TEST_ARG1(%3.6d, 123456);
		TEST_ARG1(%6.6d, 123456);
		TEST_ARG1(%9.6d, 123456);
		TEST_ARG1(%6.9d, 123456);
		TEST_ARG1(%9.9d, 123456);
		TEST_ARG1(%-6.0d, 123456);
		TEST_ARG1(%-9.0d, 123456);
		TEST_ARG1(%-6.6d, 123456);
		TEST_ARG1(%-9.6d, 123456);
		TEST_ARG1(%-6.9d, 123456);
		TEST_ARG1(%-9.9d, 123456);

		TEST_ARG1(%3.10d, 1234567);
		TEST_ARG1(%010.3d, 1234567);
		TEST_ARG1(%03.10d, 1234567);
		TEST_ARG1(%-10.3d, 1234567);
		TEST_ARG1(%3.10d, 1234567);
		TEST_ARG1(%-3.10d, 1234567);
		TEST_ARG1(%10.3d, -1234567);
		TEST_ARG1(%5.12d, -1234567);
		TEST_ARG1(%3.10d, -7654321);
		TEST_ARG1(%-3.10d, -7654321);
		TEST_ARG1(%015.3d, 1234567);

		TEST_ARG1(%-15.19d, 7654321);
		TEST_ARG1(%-15.19d, -7654321);
		TEST_ARG1(%15.d, 1234567);
		TEST_ARG1(%d, 999888777);
		TEST_ARG1(%10d, 1234567);
		TEST_ARG1(%10.0d, 1234567);
		TEST_ARG1(%10.d, 1234567);
		TEST_ARG1(%010.0d, 1234567);
		TEST_ARG1(%10.-d, 1234567);
		TEST_ARG1(%010.-12d, 1234567);
		TEST_ARG1(%d, 2147483647);
		TEST_ARG1(%d, -2147483648);


		CASE(u convert);
		TEST_ARG1(%u, 4294967295);
		TEST_ARG1(%20u, 3000000000);
		TEST_ARG1(%020u, 3000000000);
		TEST_ARG1(%20-u, 3000000000);
		TEST_ARG1(%.3u, 3000000000);
		TEST_ARG1(%.12u, 4294967295);
		TEST_ARG1(%0.10u, 4294967295);
		TEST_ARG1(%.20u, 3000000000);
		TEST_ARG1(%015.3u, 4294967295);//0フラグが取り消されるケース
		TEST_ARG1(%-12.15u, 3000000000);
		TEST_ARG1(%-15.12u, 4294967295);
		TEST_ARG1(%010u, 3000000000);
		TEST_ARG1(%010.u, 4294967295); //0が設定されてフラグ取り消し
		TEST_ARG1(%010.0u, 4294967295); //0が設定されてフラグ取り消し
		TEST_ARG2(%010.*u, -5, 3000000000);


		CASE(xX convert);
		TEST_ARG1(%x, 4294967295);
		TEST_ARG1(%20x, 3000000000);
		TEST_ARG1(%020x, 3000000000);
		TEST_ARG1(%20-x, 3000000000);
		TEST_ARG1(%.3x, 3000000000);
		TEST_ARG1(%.12x, 4294967295);
		TEST_ARG1(%.3x, 3000000000);
		TEST_ARG1(%.12x, 4294967295);
		TEST_ARG1(%0.10X, 4294967295);
		TEST_ARG1(%.20X, 3000000000);
		TEST_ARG1(%015.3X, 4294967295);//0フラグが取り消されるケース
		TEST_ARG1(%-12.15X, 3000000000);
		TEST_ARG1(%-15.12X, 4294967295);
		TEST_ARG1(%010X, 3000000000);
		TEST_ARG1(%010.X, 4294967295); //0が設定されてフラグ取り消し
		TEST_ARG1(%010.0X, 4294967295); //0が設定されてフラグ取り消し
		TEST_ARG2(%010.*X, -5, 3000000000);

		CASE(p convert);
		TEST_ARG1(%p, NULL);
		TEST_ARG1(%20p, &c);
		TEST_ARG1(%020p, &c);
		TEST_ARG1(%20-p, &c);
		TEST_ARG1(%.3p, &c);
		TEST_ARG1(%.12p, &c);
		TEST_ARG1(%.3p, &c);
		TEST_ARG1(%.12p, &c);
		TEST_ARG1(%0.10p, &c);
		TEST_ARG1(%.20p, &c);
		TEST_ARG1(%015.3p, &c);//0フラグが取り消されるケース
		TEST_ARG1(%-12.15p, &c);
		TEST_ARG1(%-15.12p, &c);//NG
		TEST_ARG1(%010p, &c);
		TEST_ARG1(%010.p, &c); //0が設定されてフラグ取り消し
		TEST_ARG1(%010.0p, &c); //0が設定されてフラグ取り消し
		TEST_ARG2(%010.*p, -5, &c);

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
		TEST_ARG1(%25.3333333333d, -111);
		//TEST_ARG1(%25.2147483648d, -111);//PC落ちるので実行不可
		TEST_ARG1(%02147483647.25d, -111); //エラー終
	}
#endif

	return 0;
}