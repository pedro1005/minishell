/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:53:24 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:53:42 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*get_next_path_token(char **path, char *path_env, char **current_token)
{
	if (!*path)
	{
		*path = path_env;
		*current_token = ft_strtok(*path, ":");
	}
	else
		*current_token = ft_strtok(NULL, ":");
	return (*current_token);
}

char	*build_full_path(char *token, char *name)
{
	if (!token || !name)
		return (NULL);
	return (ft_fullpath(token, name));
}

void	execute_command(char *full_path, t_exec *exec, t_terminal *term)
{
	struct stat	buf;

	if (access(full_path, F_OK) == 0
		&& (access(full_path, X_OK) != 0 || (stat(full_path, &buf) == 0
				&& S_ISDIR(buf.st_mode))))
	{
		g_signals = 126;
		return ;
	}
	if (access(full_path, F_OK) != 0)
	{
		g_signals = 127;
		return ;
	}
	if (exec->args)
		execve(full_path, exec->args, (char **)term->envp.buf);
	else
		execve(full_path, (char *[]){exec->name, NULL},
			(char **)term->envp.buf);
	g_signals = 127;
}

void	path_exec_cmds(char *full_path, char *name, t_terminal *term, \
		t_exec *exec)
{
	char	*path_env;
	char	*token;
	char	*path;

	path_env = ft_getenv((char **)term->envp.buf, "PATH");
	token = NULL;
	path = NULL;
	while (get_next_path_token(&path, path_env, &token) || full_path)
	{
		if (!full_path)
			full_path = build_full_path(token, name);
		execute_command(full_path, exec, term);
		free(full_path);
		full_path = NULL;
	}
	free(path_env);
	free(full_path);
}

void	create_pipe(t_tree *root, int *pipe_fd, int *pipe_created)
{
	if (root->right_tree != NULL)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		*pipe_created = 1;
	}
}
