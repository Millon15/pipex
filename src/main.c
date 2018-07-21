/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:14:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/21 20:05:47 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int				put_usage(const int errnum)
{
	char		*errstr;

	(errnum == 0) ? errstr = strerror(errno) : false;
	(errnum == 1) ? errstr = "Too less arguments" : false;
	ft_printf("ERROR: %s\n\n%s\n", errstr, \
	"Usage: ./pipex file1 cmd1 cmd2 file2");
	exit(1);
	return (1);
}

void			start(int ac, const char **av)
{
	char *const		c[4] = {"/bin/zsh", "-c", "< autor cat", NULL};
	char *const		e[1] = {NULL};
	pid_t			pid;

	((pid = fork()) == -1) ? put_usage(0) : false;
	if (pid == 0)
	{
		execve("/bin/zsh", c, e);
		put_usage(0);
	}
}

int				main(int ac, const char **av)
{
	if (ac < 5)
		put_usage(1);
	else
		start(ac, av);
	return (0);
}
