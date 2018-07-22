/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 22:46:53 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/22 23:30:55 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char			**get_path(char **env)
{
	char		**path;

	while (*env != NULL && !ft_strnequ(*env, "PATH=", 5))
		(*env)++;
	(*env == NULL) ? put_usage(2) : false;
	path = ft_strsplit(*env + 5, ':');
	return (path);
}

static char		*get_binary_path(char cmd_name[], const t_pip *p)
{
	DIR				*d;
	struct dirent	*dir;
	char			*tmp;
	char			*joined;
	int				i;

	i = 0;
	while (p->path[i])
	{
		d = opendir(p->path[i]);
		if (d)
			while ((dir = readdir(d)) != NULL)
				if (!ft_strcmp(dir->d_name, cmd_name))
				{
					closedir(d);
					tmp = ft_strjoin(p->path[i], "/");
					joined = ft_strjoin(tmp, cmd_name);
					free(tmp);
					free(cmd_name);
					return (joined);
				}
		closedir(d);
		i++;
	}
	return (NULL);
}

char			**get_cmd_arr(char cmd[], const t_pip *p)
{
	static char		**cmd_arr = NULL;
	int				i;

	if (cmd_arr != NULL)
	{
		i = 0;
		while (cmd_arr[i])
			free(cmd_arr[i++]);
		free(cmd_arr);
	}
	cmd_arr = ft_strsplit(cmd, ' ');
	cmd_arr[0] = get_binary_path(cmd_arr[0], p);
	return (cmd_arr);
}
