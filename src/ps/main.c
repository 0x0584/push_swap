#include "ps_stack.h"
#include "dlist.h"

void	del(void *foo, size_t sz)
{
	if (sz)
		free(foo);
}

int main(int argc, char *argv[])
{
	t_dlist *lst;

	lst = ft_dlstnew("head", ft_strlen("head"));

	ft_dlstpush(&lst, ft_dlstnew("two", ft_strlen("two")));
	ft_dlstpush(&lst, ft_dlstnew("third", ft_strlen("third")));
	/* ft_dlstadd(&lst, ft_dlstnew("tail", ft_strlen("tail"))); */

	printf("%s %s %s\n",
		   lst->next->content,
		   lst->next->prev->content,
		   lst->next->next->prev->content);
	puts("good");
	getchar();
	ft_dlstdel(del, &lst);

    return 0;
}
