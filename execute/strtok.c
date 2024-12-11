/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:59:06 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:59:08 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*stc_str;
	char		*token;
	int			i;

	if (str)
		stc_str = str;
	if (!stc_str)
		return (NULL);
	while (*stc_str && ft_strchr(delim, *stc_str))
		stc_str++;
	if (!*stc_str)
		return (NULL);
	token = stc_str;
	i = 0;
	while (stc_str[i] && !ft_strchr(delim, stc_str[i]))
		i++;
	if (stc_str[i])
		stc_str[i++] = '\0';
	stc_str += i;
	return (token);
}
