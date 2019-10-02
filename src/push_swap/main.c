#include "dlst.h"
int main()
{
	t_dlst head = ft_dlstnew("head", ft_strlen("this"), NULL);
	ft_dlstpush(&head, ft_dlstnew("foo", ft_strlen("thi"), NULL));
	ft_dlstpush(&head, ft_dlstnew("bar", ft_strlen("thi"), NULL));
	ft_dlstpush(&head, ft_dlstnew("fuzz", ft_strlen("thsi"), NULL));
	ft_dlstpush(&head, ft_dlstnew("buzz", ft_strlen("thsi"), NULL));
	ft_dlstpush(&head, ft_dlstnew("tail", ft_strlen("thsi"), NULL));

	printf("%s -> ", head->blob);
	printf("%s -> ", head->next->next->prev->prev->next->blob);
	printf("%s -> ", head->next->blob);
	printf("%s -> ", head->next->next->blob);
	return 0;
}
