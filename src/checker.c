/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:42:23 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 14:15:54 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "op.h"
#include "reader.h"

void	check_sort(t_ps ps_a, t_ps ps_b, t_flags *flags)
{
	bool issorted;

	issorted = ps_issorted(ps_a, ps_b);
	if (flags->color)
		ft_printf(issorted ? OK_COLOR : KO_COLOR);
	else
		ft_putendl(issorted ? "OK" : "KO");
}

int		main(int argc, char *argv[])
{
	t_ps	ps_a;
	t_ps	ps_b;
	t_lst	ops;
	t_lst	walk;
	t_flags flags;

	if (!(ps_a = read_args(argc, argv, &flags)))
		return (EXIT_FAILURE);
	ps_b = ps_alloc('B', ps_a->size);
	ops = NULL;
	if (read_input(&ops))
	{
		walk = ops;
		while (walk)
		{
			op_apply(*(t_op *)walk->content, ps_a, ps_b);
			walk = walk->next;
		}
		check_sort(ps_a, ps_b, &flags);
		ft_lstdel(&ops, lstdel_helper);
	}
	ps_del(&ps_a);
	ps_del(&ps_b);
	return (0);
}
