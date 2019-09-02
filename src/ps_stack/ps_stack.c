
#include "ps_stack.h"

t_ps_stack		*ps_stack_populate(int argc, char **argv)
{
	t_ps_stack *stk;

	stk = ps_stack_new();
	stk->length = argc - 1;
	(void)argv;
	return stk;
}

t_ps_stack		*ps_stack_new(void)
{
	t_ps_stack *stk;

	if (!(stk = ALLOC(t_ps_stack *, 1, sizeof(t_ps_stack))))
		return NULL;
	return (stk);
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
