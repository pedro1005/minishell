/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:55:27 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:55:31 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_check_flags(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args && args[i])
	{
		j = 0;
		if (args[i][0] == '-')
		{
			j++;
			while (args[i][j])
			{
				if (args[i][j] != '-' || j >= 2)
				{
					write(2, "pwd: invalid flags.\n", 20);
					g_signals = 2;
					return (1);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	ft_free_str(char *str)
{
	if (!str)
		return ;
	else
	{
		free(str);
		str = NULL;
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
	{
		ft_cd(bi->args, terminal);
		ft_free_str(terminal->current_pwd);
		terminal->current_pwd = ft_get_pwd();
	}
	else if (ft_strcmp((char *)name, "pwd") == 0)
	{
		if (ft_check_flags(bi->args))
			return ;
		ft_pwd(terminal);
	}
	else if (ft_strcmp((char *)name, "export") == 0)
		ft_export(terminal, bi->args);
	else
		exec_bi_util((char *)name, terminal, bi);
}
