/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:15:37 by coder             #+#    #+#             */
/*   Updated: 2022/10/09 22:22:05 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	free_all_paths(char **all_paths)
{
	int	i;

	i = 0;
	while (all_paths[i])
		free(all_paths[i++]);
	free(all_paths);
}

static char	*access_all_paths(char **all_paths)
{
	int		i;

	i = 0;
	while (all_paths[i])
	{
		if (!access(all_paths[i], F_OK))
		{
			if (!access(all_paths[i], X_OK))
				return (ft_strdup(all_paths[i]));
		}
		i++;
	}
	return (NULL);
}

static int	get_path_index_from_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P')
			if (envp[i][1] == 'A')
				if (envp[i][2] == 'T')
					if (envp[i][3] == 'H')
						if (envp[i][4] == '=')
							break ;
		i++;
	}
	if (envp[i])
		return (i);
	else
		return (-1);
}

static char	**cat_cmd_to_all_paths(char *cmd_arg, char **all_paths)
{
	int		i[3];
	char	*temp;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (all_paths[i[0]])
	{
		temp = malloc (sizeof (char) * (ft_strlen(cmd_arg)
					+ 2 + ft_strlen(all_paths[i[0]])));
		while (all_paths[i[0]][i[1]])
		{
			temp[i[1]] = all_paths[i[0]][i[1]];
			i[1]++;
		}
		temp[i[1]++] = '/';
		while (cmd_arg[i[2]])
			temp[i[1]++] = cmd_arg[i[2]++];
		temp[i[1]] = '\0';
		i[1] = 0;
		i[2] = 0;
		free(all_paths[i[0]]);
		all_paths[i[0]++] = temp;
	}
	return (all_paths);
}

char	*get_path(char *cmd_arg, char **envp)
{
	char	**all_paths;
	int		i;
	char	*path;

	if (!ft_strncmp(cmd_arg, ".", 1))
		return (ft_strdup(cmd_arg));
	i = get_path_index_from_envp (envp);
	if (1 < 0)
		write(2, "Error getting path index from ENVP\n", 35);
	all_paths = ft_split(envp[i] + 5, ':');
	all_paths = cat_cmd_to_all_paths(cmd_arg, all_paths);
	path = access_all_paths(all_paths);
	if (path)
	{
		free_all_paths(all_paths);
		return (path);
	}
	free_all_paths(all_paths);
	free(path);
	return (NULL);
}
