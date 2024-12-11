/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:58:32 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:58:43 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

void	ft_wait_child(t_tree *root, t_terminal *terminal)
{
	root = terminal->commands;
	while (root)
	{
		if (waitpid(root->pid, &root->status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(root->status))
			g_signals = WEXITSTATUS(root->status);
		else if (WIFSIGNALED(root->status))
			g_signals = 128 + WTERMSIG(root->status);
		else if (WIFSTOPPED(root->status))
			g_signals = 128 + WSTOPSIG(root->status);
		root = root->right_tree;
	}
}

int	ft_get_n(char **buf)
{
	int	i;

	if (!buf)
		return (0);
	i = 0;
	while (buf[i])
	{
		i++;
	}
	return (i);
}

void	exec_rh(char *line, int *i, char **delim)
{
	int	n_delim;

	n_delim = ft_get_n(delim);
	*i = 0;
	while (*i < (n_delim - 1))
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: warning: here-document ", 34);
			write(2, "delimited by end-of-file (wanted '", 34);
			write(2, delim[*i], ft_strlen(delim[*i]));
			write(2, "')\n", 3);
			(*i)++;
			continue ;
		}
		else if (ft_strcmp(line, delim[*i]) == 0)
			(*i)++;
		free(line);
	}
}

void	exec_rh_f(char *line, char **delim, int *i, int write_fd)
{
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: warning: here-document ", 34);
			write(2, "delimited by end-of-file (wanted '", 34);
			write(2, delim[*i], ft_strlen(delim[*i]));
			write(2, "')\n", 3);
			(*i)++;
			break ;
		}
		else if (ft_strcmp(line, delim[*i]) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

void	write_here_doc(int write_fd, char **delim, t_terminal *terminal)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	exec_rh(line, &i, delim);
	exec_rh_f(line, delim, &i, write_fd);
	close(write_fd);
	ft_free_cmds(terminal);
	free_dyn_arr(terminal->envp);
	free_dyn_arr(terminal->envt);
	signal(SIGINT, SIG_DFL);
	exit(0);
}
