/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel </var/spool/mail/foobar>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:56:31 by suvitiel          #+#    #+#             */
/*   Updated: 2019/10/03 16:57:03 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	ps_psh(t_ps dest, t_ps src, t_s64 node);
void	ps_swp(t_ps stk);
void	ps_rev(t_ps stk);
void	ps_rrev(t_ps stk);
