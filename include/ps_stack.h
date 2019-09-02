#ifndef PS_STACK_H
# define PS_STACK_H

# include "dlist.h"

typedef struct	s_push_swap_stack
{
	t_dlist			*head;
	t_dlist			*tail;
	size_t			length;
}				t_ps_stack;

void	ps_psh(t_ps_stack *dest, t_ps_stack *src, t_dlist *node);
void	ps_swp(t_ps_stack *stk);
void	ps_rev(t_ps_stack *stk);
void	ps_rrev(t_ps_stack *stk);

#endif
