#include <stdio.h>
#include "ft_printf.h"

#define CASE(msg) \
	printf("---[TEST] %s ---\n", # msg);

#define TEST(testcase) \
{	int std, mine; \
	printf("---\n"); \
	std = printf( #testcase "\n"); \
	mine = ft_printf( #testcase "\n"); \
	judge_retval(std, mine); \
}
#define TEST_ARG1(testcase, val1) \
{	int std, mine; \
	printf("---\n"); \
	std = printf( #testcase "\n", val1); \
	mine = ft_printf( #testcase "\n", val1); \
	judge_retval(std, mine); \
}
#define TEST_ARG2(testcase, val1, val2) \
{	int std, mine; \
	printf("---\n"); \
	std = printf( #testcase "\n", val1, val2); \
	mine = ft_printf( #testcase "\n", val1, val2); \
	judge_retval(std, mine); \
}
#define TEST_ARG3(testcase, val1, val2, val3) \
{	int std, mine; \
	printf("---\n"); \
	std = printf( #testcase "\n", val1, val2, val3); \
	mine = ft_printf( #testcase "\n", val1, val2, val3); \
	judge_retval(std, mine); \
}
void	judge_retval(int std, int mine)
{
	if (std != mine)
		printf("ret_val error(%d,%d)\n", std, mine);
}


int	main(void)
{
	char *p;
	int				i = 10;
	unsigned int	ui = 5;

	// Simple Conversion Management cspdiuxX
	CASE(Simply check each conversion without any flags);
	TEST(simply check);
	CASE(Try special cases like 0 or smallest int or empty string or null);
	TEST_ARG1(zero c\t%c,0);
	TEST_ARG1(zero d\t\t%d,0);
	TEST_ARG1(zero i\t\t%i,0);
	TEST_ARG1(zero u\t\t%u,0);
	TEST_ARG1(zero x\t\t%x,0);
	TEST_ARG1(zero X\t\t%X,0);
#if 0
	TEST_ARG1(smallest c\t%c, 0x80);
	TEST_ARG1(smallest d\t%d, 0x80000000);
	TEST_ARG1(smallest i\t%i, 0x80000000);
	TEST_ARG1(smallest u\t%u, 0x80000000);
	TEST_ARG1(smallest x\t%x, 0x80000000);
	TEST_ARG1(smallest X\t%X, 0x80000000);
#endif
	TEST_ARG1(empty string\t%s, "");
	TEST_ARG1(null pointer\t%p, NULL);
#if 0
	CASE(Try with multiple arguments/conversions);
	TEST_ARG2(string+int\t%s+%i, "string", i);
	TEST_ARG2(unsigned+decimal\t%u+%d, ui, i);
	TEST_ARG2(string+stsring\t%s+%s, "string1", "string2");
	CASE(Try the various conversions in the middle of a sentence);
	TEST_ARG3(test%d.%d.%u\t, 22, 33, 44);
	TEST_ARG3(%s.%x.%X\t, "middle", 22, 33);

	//Simple Flags Management -0.*
	CASE(Check the 'minimum file width' with values. bigger. equal and smaller than the strig);
	TEST_ARG1(%9s, "fugafuga");
	TEST_ARG1(%8s, "fugafuga");
	TEST_ARG1(%7s, "fugafuga");
	CASE(with -);
	TEST_ARG1(%-9s, "fugafuga");
	TEST_ARG1(%-8s, "fugafuga");
	TEST_ARG1(%-7s, "fugafuga");
	CASE(with 0);
	TEST_ARG1(%05d, 1234);  // Use the s conversion を使えとなってるが？？？
	TEST_ARG1(%04d, 1234);
	TEST_ARG1(%03d, 1234);

	CASE(Simple Flags Management);
	TEST_ARG1(string\t\t%s, "string");
	TEST_ARG1(string\t\t%6s, "string");
	TEST_ARG1(string\t\t%5s, "string");
	TEST_ARG1(string\t\t%7s, "string");
	TEST_ARG1(string\t\t%10s, "string");
	// %0s のケースは？flag 0 results in undefined
	TEST_ARG1(string\t\t%-10s, "string");
	//TEST_ARG1(string\t\t%07sk, "string");
	//printf("%0s", "test");
	TEST_ARG1(string\t\t%.3s, "string");
	TEST_ARG1(string\t\t%4.s, "string");

	//Advanced Flags Management
	CASE(Advanced Flags Management);
	//TEST_ARG1(minimum field\t\t%*.*s, "string");
	//TEST_ARG1(minimum.field\t\t%*.*d,-1);
	//TEST_ARG1(minimum.field\t\t%*.*d, 0);
#endif

	//Get Crazy
	CASE(Get Crazy);
	TEST(tab_\t_can_show);
	TEST(exc_\\_can_show);
	TEST(question_\?_can_show);
	TEST(percent_%%_can_show);
#if 0
	TEST_ARG1(%050.25d, -4000);
 	//TEST_ARG1(%021474.25d, -111);	//ログが見にくくなるので実施したくない
 	//TEST_ARG1(%02147483646.25d, -111); //無限ループする
 	TEST_ARG1(%02147483647.25d, -111);
#endif
	return 0;
}