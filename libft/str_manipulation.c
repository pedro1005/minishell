/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:20:00 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:20:05 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[j] = s2[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*alloc;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	alloc = malloc(sizeof(char) * (len + 1));
	if (!alloc)
		return (NULL);
	while (i < len)
	{
		alloc[i] = s[i];
		++i;
	}
	alloc[i] = '\0';
	return (alloc);
}
