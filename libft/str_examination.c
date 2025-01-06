/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_examination.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:19:23 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:19:27 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *) big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& i + j < len && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)(&big[i]));
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

int	ft_strcmp(char *str, const char *dest)
{
	if (!str || !dest)
		return (1);
	while (*str || *dest)
	{
		if ((*str != *dest) || !(*str) || !(*dest))
			return (1);
		str++;
		dest++;
	}
	return (0);
}

int	ft_is_all_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		++i;
	}
	return (i);
}
