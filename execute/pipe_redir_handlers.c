#include "../ms.h"

void	check_next_pipe(t_tree *root, int pipe_fd[2], int *pipe_created)
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
	root->pid = fork();
	if (root->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	set_child_sig();
}

int	check_heredoc(t_tree *root, int *hd_input_fd, t_terminal *terminal)
{
	if (root->redir && root->redir->delim)
	{
		*hd_input_fd = handle_here_document(root->redir->delim, terminal);
		if (*hd_input_fd == -1)
		{
			perror("Failed to process here-document");
			return (-1);
		}
	}
	return (0);
}

int	handle_here_document(char **delim, t_terminal *terminal)
{
	int		hd_fd[2];
	pid_t	hd_pid;

	if (ft_create_pipe(hd_fd, &hd_pid) == -1)
		return (-1);
	if (hd_pid == 0)
	{
		close(hd_fd[0]);
		write_here_doc(hd_fd[1], delim, terminal);
		perror("write_here_doc should not return");
		exit(1);
	}
	else
	{
		close(hd_fd[1]);
		waitpid(hd_pid, NULL, 0);
		return (hd_fd[0]);
	}
}

int	handle_input_redir(t_redir *redir, int *input_fd)
{
	if (ft_check_err_args(redir->args_in))
	{
		g_signals = 1;
		return (-1);
	}
	if (redir->type_in.sub_tk == TK_REDIR_IN
		&& redir->args_in && redir->args_in[0])
	{
		*input_fd = fd_input(redir->args_in);
		if (*input_fd == -1)
		{
			perror("Error opening input file");
			g_signals = 1;
			return (-1);
		}
	}
	return (0);
}

int	handle_output_redir(t_redir *redir, int *input_fd, int *output_fd)
{
	if ((redir->type_out.sub_tk == TK_REDIR_OUT
			|| redir->type_out.sub_tk == TK_REDIR_APP)
		&& redir->args_out && redir->args_out[0])
	{
		*output_fd = fd_output(redir->args_out);
		if (*output_fd == -1)
		{
			perror("Error opening output file");
			if (*input_fd != -1)
				close(*input_fd);
			g_signals = 1;
			return (-1);
		}
	}
	return (0);
}
