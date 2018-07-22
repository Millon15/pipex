/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:23:11 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/22 21:41:16 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libftprintf.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

typedef struct	s_pipex
{
	int			pair[2];
	int			fd[2][2];
	pid_t		pid;

}				t_pip;

#endif
