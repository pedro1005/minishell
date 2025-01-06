/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:57:39 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:57:48 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	ft_is_alpha(char c)
{
	if (!c)
		return (0);
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int	ft_is_low(char c)
{
	if (!c)
		return (0);
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	ft_is_number(char c)
{
	if (!c)
		return (0);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_exp_is_valid(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '=')
		return (0);
	if (!ft_is_alpha(str[0]) && !ft_is_low(str[0]) && str[0] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_is_alpha(str[i]) && !ft_is_low(str[i])
			&& !ft_is_number(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_utils(t_terminal *term, int *i, char **args)
{
	char	*new_var;

	if (args && args[*i] && !ft_exp_is_valid((const char *)args[*i]))
	{
		g_signals = 1;
		write(2, "export: ", 8);
		write(2, args[*i], ft_strlen(args[*i]));
		write(2, " not a valid identifier.\n", 25);
		return ;
	}
	if (ft_strchr((const char *)args[*i], '='))
	{
		ft_add_var(&term->envp, args[*i]);
		ft_add_var(&term->envt, args[*i]);
	}
	else if (ft_var_exist((char **)term->envt.buf, args[*i]))
	{
		new_var = ft_vardup((char **)term->envt.buf, (char *)args[*i]);
		ft_add_var(&term->envp, new_var);
		free(new_var);
	}
	else
		ft_add_var(&term->envp, args[*i]);
}
