#include "ms.h"

void	free_dyn_arr(t_dyn_arr dy_arr)
{
	t_dyn_arr	temp;
	int			i;

	i = 0;
	temp = dy_arr;
	while (temp.buf && temp.buf[i])
	{
		free(temp.buf[i]);
		temp.buf[i] = NULL;
		i++;
	}
	free(temp.buf);
	temp.buf = NULL;
}

void	ft_free_tokens(t_dyn_arr *tokens)
{
	t_dyn_arr	*temp;
	t_token		**list;
	int			i;

	temp = tokens;
	list = (t_token **)temp->buf;
	i = 0;
	while (list[i])
	{
		free(list[i]->s);
		list[i]->s = NULL;
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
	free(tokens);
	tokens = NULL;
}

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

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
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
