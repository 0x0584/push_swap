/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 04:08:01 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 14:11:51 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "op.h"

# define FLAG_OUT_FILE		"bar.ops"

# define FLAG_OUT			'o'
# define FLAG_VERBOSE		'v'
# define FLAG_COLOR			'c'

# define OK_COLOR						"%{green_fg}OK%{reset}\n"
# define KO_COLOR						"%{red_fg}KO%{reset}\n"

typedef struct	s_flags
{
	int		fd_out;
	bool	verbose;
	bool	color;
}				t_flags;

int				parse_flags(int argc, char **argv, t_flags *flags);
bool			read_input(t_lst *ops);
t_ps			read_args(int ac, char **av, t_flags *flags);

#endif
