/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:53:10 by coder             #+#    #+#             */
/*   Updated: 2022/10/09 00:54:03 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** If there's an OLDPWD node inside the environmentals, updates it.
** return 0 on success. It should always be a success. But if not, returns 1.
*/
int	update_oldpwd(t_ms_data *ms, char *curr_path)
{
	t_env_list	*ls_oldpwd;

	ls_oldpwd = ms->env_head;
	while (ls_oldpwd)
	{
		if (!ft_strncmp (ls_oldpwd->content, "OLDPWD=", 7))
			break ;
		ls_oldpwd = ls_oldpwd->next;
	}
	ms->oldpwd = safe_free(ms->oldpwd);
	ms->oldpwd = ft_strdup(curr_path);
	if (ls_oldpwd)
	{
		ls_oldpwd->content = safe_free(ls_oldpwd->content);
		ls_oldpwd->content = ft_strjoin("OLDPWD=", ms->oldpwd);
		return (0);
	}
	return (1);
}

/*
** If there's a PWD node inside the environmentals, updates it.
** return 0 on success and 1 on failure;
*/
int	update_pwd(t_ms_data *ms, char *path)
{
	t_env_list	*temp;

	temp = ms->env_head;
	while (temp)
	{
		if (!ft_strncmp(temp->content, "PWD=", 4))
		{
			temp->content = safe_free(temp->content);
			temp->content = ft_strjoin("PWD=", path);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
