#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "libft.h"


#define JUDGE_SIZE(name, std, mine)	\
	printf("[%s test]\t", # name); \
	if (std != mine) { \
		printf("NG:\t%zu, %zu\n", std, mine); \
	}\
	else {\
		printf("OK:\t%zu\n", std);\
	}
#define JUDGE_NUM(name, std, mine)	\
	printf("[%s test]\t", # name); \
	if (std != mine) { \
		printf("NG:\t%d, %d\n", std, mine); \
	}\
	else {\
		printf("OK:\t%d\n", std);\
	}

void	delete_list(void *content)
{
	printf("free(%s) ", content);
	free(content);
}

void	print_list(void *content)
{
	printf("%s ", content);
}

void	*operate_list(void *content)
{
	char *new_content = ft_strdup(content);
	char *p = new_content;
	while (*p)
	{
		*p++ = ft_toupper(*(char*)content++);
	}
	printf("Operate(%s) ", new_content);
	return new_content;
}

void	show_list_contents(t_list **top)
{
	t_list	*p = *top;

	if (!p)
	{
		printf("list is null\n");
		return ;
	}
	printf("show list: ");
	while (p->next != NULL)
	{
		printf("%s -> ", (char *)p->content);
		p = p->next;
	}
	printf("%s ", (char *)p->content);
	printf("\n");
}

int	main(void)
{
	t_list **top;
	t_list *p;

	//lstnew
	p = ft_lstnew(ft_strdup("NEW"));
	JUDGE_SIZE(lstnew, sizeof(t_list), sizeof(*p));
	top = &p;
	printf("[lstnew test]\t");
	show_list_contents(top);

	//lstadd_front
	t_list *p1, *p2;
	p1 = ft_lstnew(ft_strdup("100"));
	p2 = ft_lstnew(ft_strdup("200"));
	ft_lstadd_front(top, p1);
	ft_lstadd_front(top, p2);
	printf("[lstadd_front]\t");
	show_list_contents(top);

	//lstsize
	JUDGE_NUM(lstsize, 3, ft_lstsize(*top));

	//lstlast
	printf("[lstlast test]\t");
	t_list *last = ft_lstlast(*top);
	show_list_contents(&last);

	//lstadd_back
	t_list *back = ft_lstnew(ft_strdup("BACK"));
	ft_lstadd_back(top, back);
	printf("[lstadd_back]\t");
	show_list_contents(top);
	t_list *empty = (void*)0;
	ft_lstadd_back(&empty, back);
	printf("[lstadd_back]\t");
	show_list_contents(&empty);

	//lstclear(lstdelone含む)
	printf("[lstclear test]\t");
	ft_lstclear(top, delete_list);
	show_list_contents(top);
	printf("[lstclear test]\t");
	ft_lstclear(top, delete_list);
	show_list_contents(top);

	//lstiter
	printf("[lstiter test]\t");
	ft_lstiter(NULL, print_list);
	printf("\n");
	ft_lstadd_front(top, ft_lstnew(ft_strdup("apple")));
	ft_lstadd_front(top, ft_lstnew(ft_strdup("banana")));
	ft_lstadd_front(top, ft_lstnew(ft_strdup("cherry")));
	//show_list_contents(top);
	printf("[lstiter test]\t");
	ft_lstiter(*top, print_list);
	printf("\n");

	//lstmap
	printf("[lstmap test]\t");
	show_list_contents(top);
	printf("[lstmap test]\t");
	t_list *map = ft_lstmap(*top, operate_list, delete_list);
	printf("\n");
	printf("[lstmap test]\t");
	show_list_contents(&map);

	return (0);
}
