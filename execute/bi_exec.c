#include "../ms.h"
#include <signal.h>

void	ft_print_export(char **envp)
{
	char	*eql_sign;
	size_t	len_name;
	int		i;

	i = 0;
	while (envp[i])
	{
		eql_sign = ft_strchr((const char *)envp[i], '=');
		len_name = eql_sign - envp[i] + 1;
		if (eql_sign)
		{
			printf("declare -x ");
			printf("%.*s", (int)len_name, envp[i]);
			printf("\"%s\"\n", eql_sign + 1);
		}
		else
		{
			printf("declare -x %s\n", envp[i]);
		}
		i++;
	}
}

void	ft_execbi(t_exec *bi, t_terminal *terminal)
{
	const char	*name;

	if (bi && bi->name)
		name = bi->name;
	else
		name = NULL;
	if (ft_strcmp((char *)name, "echo") == 0)
		ft_echo(bi->args);
	else if (ft_strcmp((char *)name, "cd") == 0)
		ft_cd(bi->args, terminal);
	else if (ft_strcmp((char *)name, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp((char *)name, "export") == 0)
		ft_export(terminal, bi->args);
	else
		exec_bi_util((char *)name, terminal, bi);
}
