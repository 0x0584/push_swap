#ifndef DLIST_H
# define DLIST_H

# include "libft.h"

typedef struct	s_dlist
{
	void				*content;
	size_t				content_size;
	struct s_dlist		*next;
	struct s_dlist		*prev;
}				t_dlist;

t_dlist			*ft_dlstnew(void *content, size_t content_size);
void			ft_dlstdel(void (*del)(void *, size_t), t_dlist **alst);
void			ft_dlstdelone(void (*del)(void *, size_t), t_dlist **anode);
void			ft_dlstpush(t_dlist **alst, t_dlist *node);
void			ft_dlstadd(t_dlist **alst, t_dlist *node);
t_dlist			*ft_dlstpop(t_dlist **alst);
t_dlist			*ft_dlstpeek(t_dlist **alst);


#endif /* DLIST_H */
