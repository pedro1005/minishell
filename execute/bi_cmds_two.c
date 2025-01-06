/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cmds_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:54:15 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:54:19 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_pwd(t_terminal *t)
{
	char	*dir;
	char	buff[1024];

	dir = getcwd(buff, sizeof(buff));
	if (dir != NULL)
		printf("%s", dir);
	else
		printf("%s", t->current_pwd);
	printf("\n");
	g_signals = 0;
}

char	*ft_get_pwd(void)
{
	char	*dir;
	char	buff[1024];

	dir = getcwd(buff, sizeof(buff));
	if (dir)
		return (ft_strdup(dir));
	return (NULL);
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
