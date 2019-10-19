/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 05:17:52 by archid-           #+#    #+#             */
/*   Updated: 2019/10/19 13:14:40 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

#include "op.h"
#include "stack.h"

t_stack		read_args(int ac, char**av);
t_lst		read_input(void);
bool		apply_ops(t_stack stack, t_lst ops);


#endif
