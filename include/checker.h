/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 05:17:52 by archid-           #+#    #+#             */
/*   Updated: 2019/10/11 05:54:37 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

#include "op.h"

t_ps			read_args(int ac, char**av);
t_list			*read_input(void);
bool			apply_ops(t_ps stack, t_lst ops);


#endif
