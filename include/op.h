/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:16:37 by archid-           #+#    #+#             */
/*   Updated: 2019/10/23 03:54:35 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "ps.h"

enum e_which_stack
{
	APPLY_ON_A = 0,
	APPLY_ON_B, APPLY_ON_BOTH
};

enum e_op
{
	OP_PUSH = 0, OP_SWAP,
	OP_ROT, OP_RROT
};

typedef struct	s_op
{
	enum e_which_stack	which;
	enum e_op			op;
}				t_op;

bool	op_apply(t_op op, t_ps foo, t_ps bar);
bool	op_isvalid(const char *str, t_op *op);
void	op_dump(t_op op);

bool	op_dopsh(t_ps dest, t_ps src);
bool	op_doswp(t_ps stack);
bool	op_dorot(t_ps stack, bool is_up);

#endif /* OP_H */
