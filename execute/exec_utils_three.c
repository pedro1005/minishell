#include "../ms.h"

void	abst_exec(t_tree *root, t_terminal *terminal, int hd_input_fd)
{
	if (root->redir)
		ft_exec_redir(root->redir, terminal, hd_input_fd);
	else
		ft_execnode(root, terminal);
	ft_free_cmds(terminal);
	free_dyn_arr(terminal->envp);
	free_dyn_arr(terminal->envt);
	exit(g_signals);
}

int	fd_output(t_token **args)
{
	int	fd;
	int	i;

	if (!args)
		return (-1);
	i = 0;
	fd = -1;
	while (args[i])
	{
		if (args[i]->type.sub_tk == TK_REDIR_OUT)
			fd = open(args[i]->s, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			fd = open(args[i]->s, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			return (-1);
		i++;
		if (args[i])
			close(fd);
	}
	return (fd);
}

void	init_loop_values(int *pipe, int *hd_in)
{
	*pipe = 0;
	*hd_in = -1;
}

void	ft_close_fd(int fd[2])
{
	if (fd[0] != -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

char	*ft_fullpath(char *path, const char *name)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(path)
				+ ft_strlen(name) + 2));
	while (path[++i])
		res[i] = path[i];
	res[i++] = '/';
	while (name[j])
		res[i++] = name[j++];
	res[i] = '\0';
	return (res);
}
