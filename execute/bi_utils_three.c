/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:28:44 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:29:32 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

void	ft_env(t_dyn_arr env)
{
	const char	**temp = (const char **)env.buf;
	int			i;

	i = 0;
	while (temp[i])
	{
		if (ft_strchr(temp[i], '='))
			printf("%s\n", temp[i++]);
		else
			i++;
	}
	g_signals = 0;
}

int	ft_is_nflag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_util(char **args, int *nflag, int *i)
{
	*i = 1;
	if (!args || !args[*i])
	{
		printf("\n");
		g_signals = 0;
		return ;
	}
	while (args && args[*i] && args[*i][0] == '-')
	{
		if (ft_is_nflag(args[*i]))
			*nflag = 1;
		else
			break ;
		(*i)++;
	}
}
