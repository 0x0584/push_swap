#ifndef PS_STACK_H
# define PS_STACK_H

# include "dlist.h"

/* NOTE: now how to set cchunks? well i will have a list of lists
 * a chunk is just an array of two pointers on elements of the list */

/* TODO: find a way to fill the chunk */
/* TODO: create a li */
typedef struct		s_list_chunk
{
	t_dlist				*head;
	t_dlist				*tail;
	ssize_t				mid;
	size_t				size;
}					t_chunk;

typedef struct		s_ps_stack
{
	struct	s_ps_stack	*next;
	struct	s_ps_stack	*prev;
	t_chunk				*chunk;
}					t_stack, *t_pstack;

t_pstack					ps_stack_init(int argc, char **argv);
t_pstack					ps_stack_new(void);
bool						ps_stack_isempty(t_pstack stk);
void						ps_stack_dosort(t_pstack stk);

void						ps_psh(t_pstack dest, t_pstack src,
										t_dlist *node);
void						ps_swp(t_pstack stk);
void						ps_rev(t_pstack stk);
void						ps_rrev(t_pstack stk);

#endif
