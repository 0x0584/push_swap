/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/02 21:10:12 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "reader.h"
#include "ft_printf.h"

/* NOTE: for the moment solve the main case: 8 5 6 3 1 2 */
void	push_swap(t_ps a, t_ps b)
{

	ps_split_ranges(a, b);
	ps_refill(a, b);

	/* fill_stack_b(a, b, find_mids(sorted_a, mids)); */
}

int main(int argc, char **argv)
{
	t_ps		ps_a, ps_b;
	t_ps		sorted;
	t_ps_node	mids[2];
	t_dlst		walk;

	/* t_lst	ops; */
	/* t_lst	walk; */
	/* bool	failed; */
	/* t_op	*op; */

	if (!(ps_a = read_args(argc, argv)))
		return (EXIT_FAILURE);

	/* sorted = ps_mergesort(ps_a); */
	/* ft_dlstiter(ps_a->head, helper_node_dump); */
	/* op_dorot(ps_a, true); */
	/* ft_dlstiter(ps_a->head, helper_node_dump); */
	/* getchar(); */

	ps_b = ps_alloc('B', ps_a->size);
	push_swap(ps_a, ps_b);

	/* ft_printf("unsorted A\n"); */
	/* ft_dlstiter(ps_a->head, helper_node_dump); */

	/* ft_printf("sorted A\n"); */
	/* /\* ps_find_mids(sorted, mids); *\/ */
	/* ft_dlstiter(sorted->head, helper_node_dump); */

	/* ft_putendl("You will pay! Much much more!"); */

	/* ps_split_ranges(ps_a, ps_b); */
	/* ft_dlstiter(ps_a->head, helper_node_dump); */

	/* ft_putendl("//"); */
	/* ft_dlstiter(ps_b->head, helper_node_dump); */

	/* walk = sorted->tail; */
	/* while (walk) */
	/* { */
	/* 	helper_node_dump(walk); */
	/* 	walk = walk->prev; */
	/* } */

	ps_del(&ps_a);
	ps_del(&ps_b);

	/* find_mids(sorted, mids); */

	return (0);
}
