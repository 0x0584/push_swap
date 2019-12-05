/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:13:07 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 15:36:36 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "queue.h"

t_qnode *foo(int a)
{
	return queue_node(&a, sizeof(int));
}

void bar(t_qnode *node)
{
	if (node == NULL)
		return ;
	ft_printf("%p - %d\n", node->blob, *(int *)node->blob);
}

int main(int argc, char *argv[])
{
	t_queue *q = queue_init();
	t_qnode *tmp;

	queue_enq(q, foo(5));
	queue_enq(q, foo(4));
	queue_enq(q, foo(3));
	queue_push_front(q, foo(2));
	queue_push_front(q, foo(1));

	queue_iter(q, bar);

	while (queue_size(q))
	{
		ft_putendl("--------");
		bar(tmp = queue_pop(q));
		queue_node_del(&tmp, lstdel_helper);
		bar(tmp = queue_deq(q));
		queue_node_del(&tmp, lstdel_helper);
		ft_putendl("--------\n");
	}
	queue_iter(q, bar);

	queue_del(&q, lstdel_helper);

    return 0;
}
