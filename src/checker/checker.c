/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 03:56:04 by archid-           #+#    #+#             */
/*   Updated: 2019/10/12 15:24:02 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* IDEA: call each function ps_psh, ps_swp, ps_rot */

#include "checker.h"

#define BUFF_SIZE		32

/* NOTE: this should be the array, read values */
t_ps			read_args(int ac, char**av)
{
	t_ps	stack;
	long	val;
	int		i;

	i = 1;
	stack = ps_alloc('A', (size_t)ac);
	/* NOTE: if any values is not a proper `int', we should
	   stop, free everything and return NULL */
	while (i < ac)
	{
		val = ft_atoll(av[i++]);
		if (val > INT_VALMAX || val < INT_VALMIN)
		{
			ps_del(&stack);
			ft_putendl_fd("Fatal! in read_args: value is not a proper int", 2);
			break ;
		}
		ps_push(stack, (t_val)val);
	}
	return (stack);
}

/* NOTE: wait for stdin */
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

/* FIXME: add a typedef to `bool op(t_ps, t_ps, bool)' func prototype */
bool			apply_ops(t_ps stack, t_lst ops)
{
	static bool	(*op[])(t_ps, t_ps, int) = {
		[OP_PUSH] = apply_push, [OP_SWAP] = apply_swap,
		[OP_REV] = apply_rotation, [OP_RREV] = apply_rev_rotation,
		[OP_NIL] = NULL
	};
	bool		(*apply)(t_ps, t_ps, int);
	int			which_stack;
	t_ps		b;

	if (!stack || !ops)
	{
		ft_putendl_fd("Fatal! in read_input: expect non NULL argument", 2);
		return (false);
	}
	b = ps_alloc('B', PS_SIZE(stack));
	while (ops)
		if ((apply = op[apply_which((char *)ops->content, &which_stack)])
				&& apply(stack, b, which_stack))
			ops = ops->next;
		else
		{
			ft_putstr_fd("Note! failed on operation ", 2);
			ft_putendl_fd((char *)ops->content, 2);
			return (false);
		}
	return (true);
}
