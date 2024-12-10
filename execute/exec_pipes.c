#include "../ms.h"

void	abst_child(int prev_fd[2], int pipe_created, int pipe_fd[2])
{
	if (prev_fd[0] != -1)
	{
		dup2(prev_fd[0], STDIN_FILENO);
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	if (pipe_created)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	abst_parent(int prev_fd[2], int pipe_created, int pipe_fd[2])
{
	ft_close_fd(prev_fd);
	if (pipe_created)
	{
		prev_fd[0] = pipe_fd[0];
		prev_fd[1] = pipe_fd[1];
	}
	else
	{
		prev_fd[0] = -1;
		prev_fd[1] = -1;
	}
}

void	ft_abst(t_terminal *terminal)
{
	t_tree	*root;
	int		prev_fd[2];
	int		pipe_fd[2];
	int		pipe_created;
	int		hd_input_fd;

	set_fd(prev_fd, -1);
	root = terminal->commands;
	while (root)
	{
		init_loop_values(&pipe_created, &hd_input_fd);
		if (check_heredoc(root, &hd_input_fd, terminal) == -1)
			return ;
		check_next_pipe(root, pipe_fd, &pipe_created);
		if (root->pid == 0)
		{
			abst_child(prev_fd, pipe_created, pipe_fd);
			abst_exec(root, terminal, hd_input_fd);
		}
		else
			abst_parent(prev_fd, pipe_created, pipe_fd);
		root = root->right_tree;
	}
	ft_close_fd(prev_fd);
	ft_wait_child(root, terminal);
}
