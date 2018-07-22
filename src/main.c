/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:14:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/22 17:03:11 by vbrazas          ###   ########.fr       */
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

void			forkwork(const int to_stdin, const int to_stdout,\
	char *const comm[], char *const env[])
{
	pid_t			pid;

	((pid = fork()) == -1) ? put_usage(0) : false;
	if (pid == 0)
	{
		dup2(to_stdout, 1);
		close(to_stdout);
		dup2(to_stdin, 0);
		close(to_stdin);
		execve(comm[0], comm, env);
		_exit(0);
	}
}

void			start(int ac, char **av, char *const comm[], char *const env[])
{
	const int		file1 = open(av[1], O_RDONLY);
	const int		file2 = open(av[ac], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	int				pipex[2];
	int				i;

	(file1 == -1 || file2 == -1) ? put_usage(0) : false;
	((pipe(pipex)) == -1) ? put_usage(0) : false;
	i = 1;
	while (++i < ac)
	{
		((char **)comm)[2] = av[i];
		forkwork(file1, pipex[1], comm, env);
		((char **)comm)[2] = av[i];
		forkwork(pipex[0], file2, comm, env);
	}
	close(file1);
	close(file2);
	close(pipex[0]);
	close(pipex[1]);
}

int				main(int ac, char **av, char **env)
{
	char *const		comm[4] = {"/bin/zsh", "-c", "", NULL};

	if (ac < 5)
	{
		put_usage(1);
	}
	else
	{
		start(ac - 1, av, comm, env);
	}
	return (0);
}
