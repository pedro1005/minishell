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

