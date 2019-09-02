#include "dlist.h"

t_dlist			*ft_dlstnew(void *content, size_t content_size)
{
	t_dlist *lst;

	if (!(lst = ALLOC(t_dlist *, 1, sizeof(t_dlist))))
		return (NULL);
	lst->content = content ? ft_memdup(content, content_size) : NULL;
	lst->content_size = content ? content_size : 0;
	return (lst);
}

void			ft_dlstdel(void (*del)(void *, size_t), t_dlist **alst)
{
	t_dlist *walk;
	t_dlist *tmp;

	if (!SAFE_PTRVAL(alst))
		return ;
	walk = *alst;
	while (walk)
	{
		ft_putendl("here");
		tmp = walk;
		walk = walk->next;
		ft_dlstdelone(del, &tmp);
	}
	*alst = NULL;
}

void			ft_dlstdelone(void (*del)(void *, size_t), t_dlist **anode)
{

	if (!SAFE_PTRVAL(anode))
		return ;
	if ((*anode)->prev)
		(*anode)->prev->next = (*anode)->next;
	if ((*anode)->next)
		(*anode)->next->prev = (*anode)->prev;
	(*del)((*anode)->content, (*anode)->content_size);
	free(*anode);
	*anode = NULL;
}

void			ft_dlstpush(t_dlist **alst, t_dlist *node)
{
	t_dlist *walk;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = node;
		return ;
	}
	walk = *alst;
	while (walk->next)
		walk = walk->next;
	node->prev = walk;
	walk->next = node;
}

void			ft_dlstadd(t_dlist **alst, t_dlist *node)
{
	t_dlist *tmp;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = node;
		return ;
	}
	tmp = *alst;
	tmp->prev = node;
	*alst = node;
	node->next = tmp;
}

t_dlist			*ft_dlstpop(t_dlist **alst)
{
	t_dlist *poped;
	t_dlist *walk;

	if (!SAFE_PTRVAL(alst))
		return NULL;
	walk = *alst;
	while (walk->next)
		walk = walk->next;
	if (walk->prev)
		walk->prev->next = walk->next;
	poped = walk;
	return poped;
}

t_dlist			*ft_dlstpeek(t_dlist **alst)
{
	t_dlist *peeked;
	t_dlist *tmp;

	if (!SAFE_PTRVAL(alst))
		return NULL;
	tmp = *alst;
	peeked = tmp;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	*alst = tmp->next;
	return peeked;
}
