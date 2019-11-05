/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:42:23 by archid-           #+#    #+#             */
/*   Updated: 2019/11/05 14:53:35 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "op.h"
#include "reader.h"

#define STACK_SIZE 6
#define OP_NEW(op, which)		(t_op){which, op}

t_lst	example(void)
{
	t_op op;
	t_lst ops;

	ops = NULL;

	/* sa */
	op = OP_NEW(OP_SWAP, APPLY_ON_A);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));

	/* pb pb pb */
	op = OP_NEW(OP_PUSH, APPLY_ON_B);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));
	op = OP_NEW(OP_PUSH, APPLY_ON_B);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));
	op = OP_NEW(OP_PUSH, APPLY_ON_B);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));

	/* ra rb */
	op = OP_NEW(OP_ROT, APPLY_ON_BOTH);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));

	/* rra rrb */
	op = OP_NEW(OP_RROT, APPLY_ON_BOTH);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));

	/* sa */
	op = OP_NEW(OP_SWAP, APPLY_ON_A);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));

	/* pa pa pa */
	op = OP_NEW(OP_PUSH, APPLY_ON_A);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));
	op = OP_NEW(OP_PUSH, APPLY_ON_A);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));
	op = OP_NEW(OP_PUSH, APPLY_ON_A);
	ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));

	return ops;
}


int		main(int argc, char *argv[])
{
    t_ps	ps_a, ps_b;
	t_lst	ops;
	t_lst	walk;
	bool	failed;
	t_op	*op;

	if (!(ps_a = read_args(argc, argv)))
		return (EXIT_FAILURE);
	/* ps_dump(ps_a); */
	ps_b = ps_alloc('B', ps_a->size);
	/* ops = example(); */
	ops = read_input();

	walk = ops;
	failed = false;
	ft_putendl(" >>> INITIAL STATE");
	dump_stacks(ps_a, ps_b);
	ft_putendl(" ============ ");
	while (walk)
	{
		op = (t_op *)walk->content;
		op_dump(*op);
		failed = !op_apply(*op, ps_a, ps_b);
		printf("%s\n", failed ? "KO" : "OK");
		dump_stacks(ps_a, ps_b);
		ft_putendl("");
		if (failed)
			break ;
		walk = walk->next;
	}
	ft_putendl(" >>> FINAL STATE");
	dump_stacks(ps_a, ps_b);
	ft_putendl(" ============ ");

	printf("is stack sorted? %s\n", ps_issorted(ps_a, ps_b) ? "OK" : "KO");

	ft_lstdel(&ops, lstdel_helper);
	ps_del(&ps_a);
	ps_del(&ps_b);
    return 0;
}
