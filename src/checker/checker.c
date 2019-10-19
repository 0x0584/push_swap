/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 03:56:04 by archid-           #+#    #+#             */
/*   Updated: 2019/10/19 15:46:06 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* IDEA: call each function ps_psh, ps_swp, ps_rot */

#include "checker.h"
#include "op.h"

#define BUFF_SIZE		32

/* NOTE: this should be the array, read values */
t_stack			read_args(int ac, char**av)
{
	t_stack	stack;
	long	val;
	int		i;

	i = 1;
	stack = (t_stack){NULL, 'A'};
	/* NOTE: if any values is not a proper `int', we should
	   stop, free everything and return NULL */
	while (i < ac)
	{
		val = ft_atoll(av[i++]);
		if (val > INT_VALMAX || val < INT_VALMIN)
		{
			ft_lstdel(&stack.nodes, lstdel_helper);
			ft_putendl_fd("Fatal! in read_args: value is not a proper int", 2);
			break ;
		}
		ft_lstpush(&stack.nodes, ft_lstnew((int *)&val, sizeof(int)));
	}
	return (stack);
}

/* XXX: wait for stdin */
t_list			*read_input(void)
{
	char	buff[BUFF_SIZE + 1];
	short	ret;
	t_lst	ops;

	// read ops
	ops = NULL;
	while ((ret = read(0, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if (!is_op(buff))
		{

			ft_putendl_fd("Fatal! in read_input: invalid operation", 2);
			ft_lstdel(&ops, lstdel_helper);
			return (NULL);
		}
		ft_lstpush(&ops, ft_lstnew(buff, ft_strlen(buff) + 1));
	}
	return (ops);
}

void stack_dump(t_lst node)
{
	t_stack *s;

	if (node)
	{
		s = node->content;
		ft_putchar(s->symbol);

	}
}

/* FIXME: add a typedef to `bool op(t_lst, t_lst, bool)' func prototype */
bool			apply_ops(t_stack stack, t_lst ops)
{
	static bool	(*op_func[])(t_lst *, t_lst *, t_op) = {
		[OP_PUSH] = op_push, [OP_SWAP] = op_swap,
		[OP_REV] = op_rotation, [OP_RREV] = op_rev_rotation,
		[OP_NIL] = NULL
	};
	bool		(*apply)(t_lst *, t_lst *, t_op);
	int			which_stack;
	t_stack		b;
	t_op		_op;

	if (!stack.nodes || !ops)
	{
		ft_putendl_fd("Fatal! in read_input: expect non NULL argument", 2);
		return (false);
	}
	b = (t_stack){NULL, 'B'};
	which_stack = OP_TO_B;
	/* getchar(); */
	while (ops)
	{
		ft_lstiter_recu(b.nodes, stack_dump);
		ft_lstiter_recu(stack.nodes, stack_dump);
		_op = op_which((char *)ops->content);
		printf("OP: %d  WHICH: %d\n", _op.op, _op.which);
		getchar();
		/* getchar(); */
		if ((apply = op_func[_op.op]) && apply(&stack.nodes, &b.nodes, _op))
			ops = ops->next;
		else
		{
			ft_putstr_fd("Note! failed on op ", 2);
			ft_putendl_fd((char *)ops->content, 2);
			return (false);
		}
	}
	return (true);
}
