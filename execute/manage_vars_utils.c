/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:55:02 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:55:11 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*get_var_name(char *var)
{
	size_t	i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i += 1;
	name = (char *)malloc((sizeof(char) * i) + 1);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		name[i] = var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_get_clean_var_name(char *var)
{
	if (!var)
		return (NULL);
	if (ft_strchr((const char *)var, '='))
		return (get_var_name(var));
	return (ft_strdup(var));
}
