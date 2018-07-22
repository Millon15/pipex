/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:14:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/22 23:32:10 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int				put_usage(const int errnum)
{
	char		*errstr;

	(errnum == 0) ? errstr = strerror(errno) : false;
	(errnum == 1) ? errstr = "Too less arguments" : false;
	(errnum == 2) ? errstr = "Cannot find binary of the given command" : false;
	(errnum == 3) ? errstr = "ft_strjoin fail" : false;
	ft_printf("ERROR: %s\n\n%s\n", errstr, \
	"Usage: ./pipex file1 cmd1 cmd2 file2");
	exit(1);
	return (1);
}

static	void	closer(t_pip *p)
{
	(close(p->fd[0][0]) == -1) ? put_usage(0) : false;
	(close(p->fd[0][1]) == -1) ? put_usage(0) : false;
	(close(p->fd[1][0]) == -1) ? put_usage(0) : false;
	(close(p->fd[1][1]) == -1) ? put_usage(0) : false;
	while (wait(NULL) > 0)
		;
}

static	void	performfork(t_pip *p, int i, char **av, char **env)
{
	static char			**cmd_arr;

	cmd_arr = get_cmd_arr(av[2 + i], p);
	((p->pid = fork()) == -1) ? put_usage(0) : false;
	if (p->pid == 0)
	{
		(dup2(p->fd[i][0], 0) == -1) ? put_usage(0) : false;
		(dup2(p->fd[i][1], 1) == -1) ? put_usage(0) : false;
		(close(p->fd[!(i % 2)][0]) == -1) ? put_usage(0) : false;
		(close(p->fd[!(i % 2)][1]) == -1) ? put_usage(0) : false;
		(execve(cmd_arr[0], cmd_arr, env) == -1) ? put_usage(0) : false;
	}
}

int				main(int ac, char **av, char **env)
{
	t_pip			p;

	(ac < 5) ? put_usage(1) : false;
	(pipe(p.pair) == -1) ? put_usage(0) : false;
	p.fd[0][0] = open(av[1], O_RDONLY);
	p.fd[0][1] = p.pair[1];
	p.fd[1][0] = p.pair[0];
	p.fd[1][1] = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	(p.fd[0][0] == -1 || p.fd[1][1] == -1) ? put_usage(0) : false;
	p.path = get_path(env);
	performfork(&p, 0, av, env);
	performfork(&p, 1, av, env);
	closer(&p);
	return (0);
}
