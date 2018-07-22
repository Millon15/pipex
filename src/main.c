/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:14:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/22 21:45:59 by vbrazas          ###   ########.fr       */
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

static void		forkwork(t_pip *p, int i, \
	char *const comm[], char *const env[])
{
	(dup2(p->fd[i][0], 0) == -1) ? put_usage(0) : false;
	(dup2(p->fd[i][1], 1) == -1) ? put_usage(0) : false;
	(close(p->fd[!(i % 2)][0]) == -1) ? put_usage(0) : false;
	(close(p->fd[!(i % 2)][1]) == -1) ? put_usage(0) : false;
	(execve(comm[0], comm, env) == -1) ? put_usage(0) : false;
}

int				main(int ac, char **av, char **env)
{
	t_pip			p;
	char *const		comm[4] = {"/bin/zsh", "-c", "", NULL};

	(ac < 5) ? put_usage(1) : false;
	(pipe(p.pair) == -1) ? put_usage(0) : false;
	p.fd[0][0] = open(av[1], O_RDONLY);
	p.fd[0][1] = p.pair[1];
	p.fd[1][0] = p.pair[0];
	p.fd[1][1] = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	(p.fd[0][0] == -1 || p.fd[1][1] == -1) ? put_usage(0) : false;
	((char **)comm)[2] = av[2];
	((p.pid = fork()) == -1) ? put_usage(0) : false;
	(p.pid == 0) ? forkwork(&p, 0, comm, env) : false;
	((char **)comm)[2] = av[3];
	((p.pid = fork()) == -1) ? put_usage(0) : false;
	(p.pid == 0) ? forkwork(&p, 1, comm, env) : false;
	closer(&p);
	return (0);
}
