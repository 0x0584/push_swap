
#include "ps_stack.h"

t_ps_stack		ps_stack_new(void)
{
	t_stack *stk;

	if (!(stk = ALLOC(t_stack *, 1, sizeof(t_stack))))
		return (NULL);
	if (!(stk->chunk = ALLOC(t_chunk *, 1, sizeof(t_chunk))))
	{
		free(stk);
		return (NULL);
	}
	return (stk);
}

t_ps_stack		ps_stack_init(int argc, char **argv)
{
	t_ps_stack	stk;

	if (argc < 2)
		return (NULL);
	while (argc-- > 2)
	return stk;
}

bool			ps_stack_isempty(t_ps_stack *stk)
{
	if (!stk)
		return false;
	return (stk->length == 0);
}

void			ps_stack_dosort(t_ps_stack *stk)
{
	(void)stk;
}
