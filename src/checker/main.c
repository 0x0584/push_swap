/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 22:54:00 by archid-           #+#    #+#             */
/*   Updated: 2019/10/19 14:25:25 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		exit_log(const char *s)
{
	ft_putendl(s);
	return (ft_strcmp(s, "KO") ? -1 : 0);
}

/* this is teh checkers main */
/* compile using
   gcc -Wall -Wextra -ggdb src/checker\/\*.c core\/\*.c -o foo -Llibft -lft -Iinclude -Ilibft
*/

int		int_cmp(t_lst a, t_lst b)
{
	if (a && b)
		return ((*(int *)a->content) - (*(int *)b->content));
	return (-1);
}

bool	is_sorted(t_lst lst)
{
	t_lst	sorted;
	t_lst	walk;
	bool	flag;

	flag = true;
	sorted = ft_lstdup(lst);
	ft_lst_mergesort(&sorted, int_cmp);
	walk = sorted;
	while (walk)
	{
		if (*(int *)walk->content != *(int *)lst->content)
		{
			flag = false;
			break;
		}
		walk = walk->next;
		lst = lst->next;
	}
	ft_lstdel(&sorted, lstdel_helper);
	return flag;
}

int		main(int argc, char *argv[])
{
	t_stack	ps;
	t_lst	ops;

	if (argc == 1)
		return -1;
	ps = read_args(argc, argv);
	ops = read_input();
	apply_ops(ps, ops);
	ft_putendl(is_sorted(ps.nodes) ? "OK" : "KO");
	ft_lstdel(&ops, lstdel_helper);
	ft_lstdel(&ps.nodes, lstdel_helper);
	return (0);
}
