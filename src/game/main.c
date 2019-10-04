/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:38:48 by archid-           #+#    #+#             */
/*   Updated: 2019/10/04 02:06:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

/* think about creating a log library */
#define POP(s) 	ft_putstr("poped: "); ft_putnumber(ps_pop(s));	\
	ft_putendl("")
#define PUSH(s, e) ft_putstr("pushed: "); ft_putnumber(e);	\
	ps_push(s, e); ft_putendl("")

int main(int argc, char *argv[])
{
    t_ps stack_a = ps_alloc(30);

	ps_dump(stack_a);

	PUSH(stack_a, 1);
	ps_dump(stack_a);
	PUSH(stack_a, 2);
	PUSH(stack_a, 3);
	ps_dump(stack_a);
	PUSH(stack_a, 4);
	PUSH(stack_a, 5);

	ps_dump(stack_a);

	POP(stack_a);
	POP(stack_a);
	ps_dump(stack_a);
	POP(stack_a);
	POP(stack_a);

	ps_dump(stack_a);

	PUSH(stack_a, 2);
	PUSH(stack_a, 3);
	ps_dump(stack_a);
	PUSH(stack_a, 4);

	ps_dump(stack_a);

	POP(stack_a);
	POP(stack_a);
	POP(stack_a);
	POP(stack_a);

	ps_dump(stack_a);
	ps_del(&stack_a);

    return 0;
}
