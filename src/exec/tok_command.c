/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:53:46 by coder             #+#    #+#             */
/*   Updated: 2022/10/06 01:46:47 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Concatenates the command from a token into all possible paths from the
** environmental variable, returns the pointer to it.
*/
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

/*
** Tests all paths to check wether the command is accessible
*/
static char	*access_all_paths(char **pp)
{
	int		i;

	i = 0;
	while (pp[i])
	{
		if (!access(pp[i], F_OK))
		{
			if (!access(pp[i], X_OK))
				return (ft_strdup(pp[i]));
		}
		i++;
	}
	return (NULL);
}

/*
** returns the path of the sent command
*/
static char	*tok_get_path(char *value, t_env_list *env_head)
{
	t_env_list	*temp;
	char		**all_paths;
	char		*path;

	temp = env_head;
	if (!ft_strncmp(value, ".", 1))
		return (ft_strdup(value));
	if (value[0] == '\0')
		return (ft_strdup(value));
	while (temp && ft_strncmp(temp->content, "PATH=", 5))
		temp = temp->next;
	if (!temp)
		return (NULL);
	all_paths = ft_split(temp->content + 5, ':');
	all_paths = cat_cmd_to_all_paths(value, all_paths);
	path = access_all_paths(all_paths);
	all_paths = free_pp_char(all_paths);
	return (path);
}

/*
** Checks if there's a command from index onwards.
** Creates a heap allocated string of given command or builtin, ready to be
** sent to execution.
*/
char	*tok_command(t_ms_data *ms, t_com *self)
{
	t_tokens	*temp;
	char		*path;

	path = NULL;
	temp = iterate_to_tok_index(ms);
	while (temp && (temp->type != COMTOKEN && temp->type != BITOKEN))
		temp = temp->next;
	if (!temp)
		return (NULL);
	if (temp->type == BITOKEN)
	{
		self->is_builtin = 1;
		return (ft_strdup(temp->value));
	}
	if (temp->type == COMTOKEN)
		path = tok_get_path(temp->value, ms->env_head);
	if (!path)
	{
		self->error_to_print = ft_strjoin(temp->value, ": command not found\n");
		return (ft_strdup(temp->value));
	}
	return (path);
}
