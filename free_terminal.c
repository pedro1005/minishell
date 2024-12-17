/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:08:07 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:09:30 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	ft_free_cmds(t_terminal *terminal)
{
	t_tree	*cmd;

	if (!terminal->commands)
		return ;
	cmd = terminal->commands;
	while (cmd)
	{
		if (cmd && cmd->exec)
			ft_free_exe(cmd->exec);
		ft_free_redir(cmd);
		if (cmd->right_tree)
		{
			cmd = cmd->right_tree;
			free(cmd->left_tree);
			cmd->left_tree = NULL;
		}
		else
			break ;
	}
	free(cmd);
	cmd = NULL;
}

void	ft_free_redir(t_tree *cmd)
{
	int	i;

	if (!cmd->redir)
		return ;
	i = 0;
	while (cmd->redir->args_out && cmd->redir->args_out[i])
	{
		free(cmd->redir->args_out[i]->s);
		cmd->redir->args_out[i]->s = NULL;
		free(cmd->redir->args_out[i]);
		cmd->redir->args_out[i] = NULL;
		i++;
	}
	free(cmd->redir->args_out);
	ft_free_args(cmd->redir->args_in);
	ft_free_exe(cmd->redir->exec);
	if (cmd->redir->delim)
		ft_free_args(cmd->redir->delim);
	free(cmd->redir);
	cmd->redir = NULL;
}

void	ft_free_exe(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->args)
		ft_free_args(exec->args);
	if (exec->name)
	{
		free(exec->name);
		exec->name = NULL;
	}
	free(exec);
	exec = NULL;
}
