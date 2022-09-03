#include "../../headers/minishell.h"

pid_t	create_child(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("child");
		exit(EXIT_FAILURE);
	}
	return (child_pid);
}

int	get_exec_error(char *path, t_ms_data *ms)
{
	if (!path)
		ms->exit_code = -1;
	else if (access(path, X_OK))
		ms->exit_code = -2;
	return (ms->exit_code);
}

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

char	*get_path(char *cmd_arg, char **envp)
{
	char	**all_paths;
	int		i;
	char	*path;

	i = get_path_index_from_envp (envp);
	if (1 < 0)
		perror("Error getting path index from ENVP");
	all_paths = ft_split(envp[i] + 5, ':');
	all_paths = cat_cmd_to_all_paths(cmd_arg, all_paths);
	path = access_all_paths(all_paths);
	if (path)
	{
		i = 0;
		while (all_paths[i])
		{
			free(all_paths[i]);
			i++;
		}
		free(all_paths);
		return (path);
	}
	free_all_paths(all_paths);
	free(path);
	return (NULL);
}

/*
** execve para testes. deletar após implementar tudo direitinho
** pega o primeiro argumento da linha e usa como comando.
** retorna statsu de saída do filho
*/
int	exec_MVP_TESTE(t_ms_data *ms, char **envp)
{
	char	*path;
	int		pid;
	int 	e_status;

	e_status = 0;
	pid = create_child();
	if (pid)
	{
		waitpid(pid, &e_status, 0);
	}
	if (!pid)
	{
		path = get_path(ms->rl_split[0], envp);
		if (!get_exec_error(path, ms))
			execve(path, ms->rl_split, envp);
		else
		{
			printf("command not foun!\n");
		}
		safe_free(path);
		path = NULL;
		exit(e_status);
	}
		printf ("\n\nexit status: %d\n\n", e_status);
		return (0);
}
