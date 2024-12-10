#include "../ms.h"

void	ft_execve(t_exec *exec, t_terminal *terminal)
{
	char	*full_path;
	char	*name;

	name = exec->name;
	full_path = NULL;
	if (exec->type.sub_tk == TK_PATH)
	{
		full_path = ft_strdup(exec->name);
		execute_command(full_path, exec, terminal);
		free(full_path);
	}
	else
		path_exec_cmds(full_path, name, terminal, exec);
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
	return ;
}

void	ft_execnode(t_tree *node, t_terminal *terminal)
{
	if (node && node->exec && node->exec->type.sub_tk && \
			(node->exec->type.sub_tk == TK_EXEC
			|| node->exec->type.sub_tk == TK_PATH))
	{
		ft_execve(node->exec, terminal);
		return ;
	}
	else
	{
		ft_execbi(node->exec, terminal);
		return ;
	}
}

void	ft_exec_fd(t_exec *exec, int input_fd,
			int output_fd, t_terminal *terminal)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_exec_fd_child(exec, input_fd, output_fd, terminal);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error waiting for child process");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			g_signals = WEXITSTATUS(status);
	}
}

void	ft_exec_redir(t_redir *redir, t_terminal *terminal, int hd_input_fd)
{
	int	input_fd;
	int	output_fd;

	input_fd = hd_input_fd;
	output_fd = -1;
	if (handle_input_redir(redir, &input_fd) == -1)
		return ;
	if (handle_output_redir(redir, &input_fd, &output_fd) == -1)
		return ;
	if (redir->exec)
		ft_exec_fd(redir->exec, input_fd, output_fd, terminal);
	if (input_fd != -1)
		close(input_fd);
	if (output_fd != -1)
		close(output_fd);
}

void	execute(t_terminal *terminal)
{
	if (!terminal->commands->exec && !terminal->commands->redir
		&& !terminal->commands->right_tree)
		return ;
	if (!terminal->commands->right_tree && terminal->commands->exec
		&& (terminal->commands->exec->type.sub_tk == TK_BUILT_IN
			|| terminal->commands->exec->type.sub_tk == TK_EQL))
		ft_execbi(terminal->commands->exec, terminal);
	else
	{
		set_child_sig();
		ft_abst(terminal);
	}
	return ;
}
