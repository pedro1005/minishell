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

char	*ft_get_clean_var_name(char *var)
{
	if (!var)
		return (NULL);
	if (ft_strchr((const char *)var, '='))
		return (get_var_name(var));
	return (ft_strdup(var));
}
