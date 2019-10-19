/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:56:31 by archid-           #+#    #+#             */
/*   Updated: 2019/10/19 15:43:41 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	do_psh(t_lst *stack_dest, t_lst *stack_src)
{
	if (!SAFE_PTRVAL(stack_src) || !ft_lstlen(*stack_src))
	{
		ft_putendl_fd("Fatal! in do_psh: using (PUSH operation)"
					  " with empty source stack", 2);
		return ;
	}
	ft_lstpush(stack_dest, ft_lstpop(stack_src));
}

void	do_swp(t_lst *stack)
{
	t_lst foo;
	t_lst bar;

	if (!SAFE_PTRVAL(stack) || ft_lstlen(*stack) < 2)
	{
		ft_putendl_fd("Error! is do_swp: using (SWAP operation)"
					  " while stack has less than two elements to swap", 2);
		return ;
	}
	foo = ft_lstpop(stack);
	bar = ft_lstpop(stack);
	ft_lstpush(stack, foo);
	ft_lstpush(stack, bar);
}

void	do_rot(t_lst *stack, bool isup)
{
	size_t	len;

	if (!SAFE_PTRVAL(stack))
		return ;
	len = ft_lstlen(*stack);
	if ((len = ft_lstlen(*stack)) < 2)
	{
		ft_putendl_fd("Warning! do_rot: using (ROTATE operation) but"
					  " has not been affected", 2);
		return ;
	}
	else if (len == 2)
	{
		do_swp(stack);
		ft_putendl_fd("Note! do_rot: using SWAP instead of ROTATION", 2);
		return ;
	}
	if (isup)
		ft_lstadd(stack, ft_lstpop(stack));
	else
		ft_lstpush(stack, ft_lstpeek(stack));
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
