/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:33:10 by archid-           #+#    #+#             */
/*   Updated: 2019/10/09 11:49:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "stack.h"

t_ps	read_stack(int argc, char **argv)
{
	t_ps	stack;
	t_s64	val;
	int		i;

	i = 1;
	stack = NULL;
	while (i < argc)
	{
		val = ft_atoll(argv[i++]);
		if (val > INT_VALMAX || val < INT_VALMIN)
		{
			ps_del(&stack);
			return (NULL);
		}
		ps_push(stack, (t_val)val);
	}
	return (stack);
}

/* FIXME: this is should be done using quick-sort */
void	sort_asc_stack(t_ps stack)
{
	(void)stack;
}

/* FIXME: this waits for stdin */
void	read_ops(t_ps stack)
{

}

#endif
