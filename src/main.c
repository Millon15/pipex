/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:14:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/21 21:36:46 by vbrazas          ###   ########.fr       */
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

char			*pipex_join(char *str1, char *str2)
{
	char *tmp2;

	tmp2 = str1;
	str1 = ft_strjoin(str1, str2);
	free(tmp2);
	return (str1);
}

char			*pars(int ac, char **av)
{
	int		i;
	char	*str;

	i = 0;
	while (++i < ac)
	{
		if (i == 1)
			str = ft_strjoin("< ", av[i]);
		else if (i == ac - 1)
		{
			str = pipex_join(str, " > ");
			str = pipex_join(str, av[i]);
		}
		else
		{
			str = pipex_join(str, " ");
			str = pipex_join(str, av[i]);
			if (i != ac - 2)
				str = pipex_join(str, " |");
		}
	}
	return (str);
}

void			start(int ac, char **av)
{
	char *const		c[4] = {"/bin/zsh", "-c", pars(ac, av), NULL};
	char *const		e[1] = {NULL};
	pid_t			pid;

	((pid = fork()) == -1) ? put_usage(0) : false;
	if (pid == 0)
	{
		execve("/bin/zsh", c, e);
		put_usage(0);
	}
	free(c[2]);
}

int				main(int ac, char **av)
{
	if (ac < 5)
		put_usage(1);
	else
		start(ac, av);
	return (0);
}
