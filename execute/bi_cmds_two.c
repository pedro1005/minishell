#include "../ms.h"

void	ft_export(t_terminal *terminal, char **args)
{
	int	i;

	if (!args || !args[1])
	{
		ft_print_export((char **)terminal->envp.buf);
		return ;
	}
	i = 1;
	g_signals = 0;
	while (args[i])
	{
		export_utils(terminal, &i, args);
		i++;
	}
}

void	ft_pwd(void)
{
	char	*dir;
	char	buff[1024];

	dir = getcwd(buff, sizeof(buff));
	if (dir != NULL)
		printf("%s", dir);
	printf("\n");
	g_signals = 0;
}

char	*ft_get_pwd(void)
{
	char	*dir;
	char	buff[1024];

	dir = getcwd(buff, sizeof(buff));
	return (ft_strdup(dir));
}

char	*ft_getenv(char **env, char *str)
{
	int		i;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	i = 0;
	while (env[i])
	{
		name = get_var_name(env[i]);
		if (ft_strcmp(name, (const char *)str) == 0)
		{
			value = ft_strdup(get_var_value(env[i]));
			free(name);
			return (value);
		}
		i++;
		free(name);
	}
	return (value);
}
