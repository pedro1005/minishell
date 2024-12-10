#include "../ms.h"

void	ft_exit(t_terminal *terminal, t_exec *bi)
{
	g_signals = 0;
	if (bi->args && bi->args[2])
	{
		write(2, "minishell: too many arguments\n", 31);
		g_signals = 1;
	}
	else if (bi->args && bi->args[1] && !ft_isnumber(bi->args[1]))
	{
		write(2, "minishell: numeric argument required\n", 38);
		g_signals = 2;
	}
	else if (bi->args && bi->args[1])
	{
		g_signals = ft_atoi(bi->args[1]);
		while (g_signals < 0)
			g_signals += 256;
		while (g_signals > 255)
			g_signals -= 256;
	}
	ft_free_cmds(terminal);
	free_dyn_arr(terminal->envp);
	free_dyn_arr(terminal->envt);
	exit(g_signals);
}

void	cd_no_path(char *path, char *home, char *current_pwd)
{
	write(2, "cd: ", 4);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	g_signals = 1;
	free(current_pwd);
	free(home);
}

void	ft_cd(char **path, t_terminal *terminal)
{
	char		*home;
	char		*current_pwd;
	char		*oldpwd;

	if (path && path[2])
	{
		write(2, "cd: too many arguments.\n", 24);
		g_signals = 1;
		return ;
	}
	current_pwd = ft_get_pwd();
	home = ft_getenv((char **)terminal->envp.buf, "HOME");
	oldpwd = NULL;
	if (!path)
	{
		cd_utils(home, oldpwd, current_pwd, terminal);
		g_signals = 0;
		return ;
	}
	else if (chdir(path[1]) != 0)
	{
		cd_no_path(path[1], home, current_pwd);
		return ;
	}
	cd_utils_two(home, oldpwd, current_pwd, terminal);
}

void	ft_echo(char **args)
{
	int	i;
	int	nflag;

	if (!args)
	{
		printf("\n");
		return ;
	}
	nflag = 0;
	echo_util(args, &nflag, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (!nflag)
		printf("\n");
	g_signals = 0;
}

void	ft_unset(t_terminal *terminal, char **token)
{
	t_dyn_arr	env;
	char		**envp;
	int			i;

	env = terminal->envp;
	envp = (char **)env.buf;
	i = 0;
	while (envp[i])
		unset_utils(envp, token, env, &i);
	terminal->envp = env;
	env = terminal->envt;
	envp = (char **)env.buf;
	i = 0;
	while (envp[i])
		unset_utils(envp, token, env, &i);
	terminal->envt = env;
	g_signals = 0;
}
