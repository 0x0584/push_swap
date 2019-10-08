/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:38:48 by archid-           #+#    #+#             */
/*   Updated: 2019/10/08 03:47:51 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

/* think about creating a log library */
#define POP(s)			ft_putstr("poped: "); \
	ft_putnumber(ps_pop(s));				  \
	ft_putendl("")
#define PUSH(s, e)		ft_putstr("pushed: "); \
	ft_putnumber(e);						   \
	ps_push(s, e);							   \
	ft_putendl("")
#define ROT(s, u)		ft_putstr(u ? "rot up" : "rot down");	\
	ps_rot(s, u);												\
	ft_putendl("")
int main(void)
{
    t_ps stack_a = ps_alloc('A', 30);
    t_ps stack_b = ps_alloc('B', 30);

	/* ps_dump(stack_a); */
	/* ps_dump(stack_a); */

	PUSH(stack_a, 1);
	/* ps_dump(stack_a); */
	PUSH(stack_a, 2);
	PUSH(stack_a, 3);
	/* ps_dump(stack_a); */
	PUSH(stack_a, 4);
	PUSH(stack_a, 5);

	/* ps_dump(stack_a); */

	POP(stack_a);
	POP(stack_a);
	/* ps_dump(stack_a); */
	POP(stack_a);
	POP(stack_a);
	POP(stack_a);
	POP(stack_a);

	/* ps_dump(stack_a); */

	PUSH(stack_a, 11);
	PUSH(stack_a, -1);
	/* ps_dump(stack_a); */
	PUSH(stack_a, 5);

	/* ps_dump(stack_a); */

	/* POP(stack_a); */
	/* POP(stack_a); */
	/* POP(stack_a); */
	/* POP(stack_a); */

	ps_psh(stack_b, stack_a);
	/* ps_swp(stack_a); */
	ps_psh(stack_b, stack_a);
	/* ps_swp(stack_b); */
	ps_psh(stack_b, stack_a);
	/* ps_swp(stack_b); */
	ps_psh(stack_b, stack_a);

	/* printf("{%ld}", *stack_b->tail); */
	/* POP(stack_b); */
	/* POP(stack_b); */
	/* PUSH(stack_b, 69); */
	PUSH(stack_b, 1);
	PUSH(stack_b, 2);

	/* ps_dump(stack_b); */

	/* printf("{%p}", (void *)stack_b->tail); */
	ps_swp(stack_b);
	/* printf("{%p}", (void *)stack_b->tail); */


	ps_dump(stack_b);
	ROT(stack_b, true);
	ps_dump(stack_b);
	PUSH(stack_b, 111);
	ps_dump(stack_b);
	ft_putendl("below");
	ROT(stack_b, false);
	ps_dump(stack_b);
	PUSH(stack_b, 4);
	/* ps_rot(stack_b, false); */
	PUSH(stack_b, 5);
	ps_dump(stack_b);

	ps_del(&stack_a);
	ps_del(&stack_b);


    return 0;
}
