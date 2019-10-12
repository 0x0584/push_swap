/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:56:31 by archid-           #+#    #+#             */
/*   Updated: 2019/10/12 15:41:12 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	ps_psh(t_ps stack_dest, t_ps stack_src)
{
	if (!stack_dest || !stack_src || PS_ISEMPTY(stack_src))
	{
		ft_putendl_fd("Fatal! in ps_psh: using (PUSH operation)"
					  " with empty source stack", 2);
		return ;
	}
	ps_push(stack_dest, ps_pop(stack_src));
}

void	ps_swp(t_ps stack)
{
	t_val foo;
	t_val bar;

	if (!stack || PS_LENGTH(stack) < 2)
	{
		ft_putendl_fd("Error! is ps_swp: using (SWAP operation)"
					  " while stack has less than two elements to swap", 2);
		return ;
	}
	foo = ps_pop(stack);
	bar = ps_pop(stack);
	ps_push(stack, foo);
	ps_push(stack, bar);
}

void	ps_rot(t_ps stack, bool isup)
{
	t_val	poped;
	size_t	i;
	size_t	len;

	if (!stack || PS_ISEMPTY(stack) || PS_LENGTH(stack) < 2)
	{
		ft_putendl_fd("Warning! ps_rot: using (ROTATE operation) but"
					  " has not been affected", 2);
		return ;
	}
	else if (PS_LENGTH(stack) == 2)
	{
		ps_swp(stack);
		ft_putendl_fd("Note! ps_rot: using SWAP instead of ROTATION", 2);
		return ;
	}
	i = 0;
	len = (size_t)PS_LENGTH(stack);
	stack->mark++;				/* set mark into place */
	poped = *(isup ? stack->mark : stack->tail);
	while (i < len)
	{
		if (isup)
			stack->mark[i] = stack->mark[i + 1];
		else
			stack->mark[len - i] = stack->mark[len - i - 1];
		i++;
	}
	*(isup ? stack->tail : stack->mark) = poped;
	stack->mark--;				/* set mark into place */
}

#define END(s, i)					(s[i] == '\n' && s[i + 1] == '\0')

bool	is_op(const char *s)
{
	if (*s && s[1] && ft_strchr("psr", *s) && ft_strchr("absr", s[1]))
	{
		if (s[1] == 'r' && s[2] && ft_strchr("ab", s[2]) && END(s, 3))
			return (true);
		return (END(s, 2));
	}
	return (false);
}
