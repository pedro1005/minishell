/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:56:06 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:56:11 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

void	set_fd(int fd[2], int num)
{
	fd[0] = num;
	fd[1] = num;
}

void	ft_check_fd(int fd, int fileno)
{
	if (fd != -1)
	{
		if (dup2(fd, fileno) == -1)
		{
			perror("Error duplicating file descriptor");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	ft_exec_fd_child(t_exec *exec, int input_fd,
			int output_fd, t_terminal *terminal)
{
	ft_check_fd(input_fd, STDIN_FILENO);
	ft_check_fd(output_fd, STDOUT_FILENO);
	if (exec->type.sub_tk == TK_EXEC)
	{
		g_signals = 0;
		ft_execve(exec, terminal);
		exit(EXIT_FAILURE);
	}
	else if (exec->type.sub_tk == TK_BUILT_IN)
	{
		ft_execbi(exec, terminal);
		ft_free_cmds(terminal);
		free_dyn_arr(terminal->envp);
		free_dyn_arr(terminal->envt);
		exit(0);
	}
}

int	fd_input(char **args)
{
	int	fd;
	int	i;

	if (!args)
		return (-1);
	i = 0;
	fd = -1;
	while (args[i])
		i++;
	fd = open(args[i - 1], O_RDONLY);
	return (fd);
}

int	ft_create_pipe(int fd[2], pid_t *pid)
{
	if (pipe(fd) == -1)
	{
		perror("Error creating pipe");
		return (-1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("Error forking for here document");
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	set_child_sig();
	return (0);
}
