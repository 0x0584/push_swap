/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 22:54:00 by archid-           #+#    #+#             */
/*   Updated: 2019/10/12 15:20:41 by archid-          ###   ########.fr       */
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

int main(int argc, char *argv[])
{
	t_ps	ps;
	t_lst	ops;

	ps = read_args(argc, argv);
	ops = read_input();
	ft_putendl(!apply_ops(ps, ops) || !ps_issorted(ps) ? "KO" : "OK");
	ps_del(&ps);
	ft_lstdel(&ops, lstdel_helper);
	return (0);
}
