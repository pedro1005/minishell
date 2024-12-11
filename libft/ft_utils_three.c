/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:04:32 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:04:34 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

static int	ft_order_of_magnitude(int n)
{
	int	om;

	om = 0;
	if (n <= 0)
		om++;
	while (n != 0)
	{
		n = n / 10;
		om++;
	}
	return (om);
}

static char	*ft_create_string(unsigned int magnitudeorder)
{
	char	*string;

	string = (char *)malloc((magnitudeorder + 1) * sizeof(char));
	if (!string)
		return (NULL);
	string[magnitudeorder] = 0;
	return (string);
}

char	*ft_itoa(int n)
{
	unsigned int	magnitudeorder;
	long			temp;
	char			*ptr;

	magnitudeorder = ft_order_of_magnitude(n);
	ptr = ft_create_string(magnitudeorder);
	temp = n;
	if (!ptr)
		return (NULL);
	if (temp < 0)
	{
		ptr[0] = '-';
		temp *= -1;
	}
	if (temp == 0)
		ptr[0] = '0';
	magnitudeorder--;
	while (temp != 0)
	{
		ptr[magnitudeorder] = (temp % 10) + '0';
		temp = temp / 10;
		magnitudeorder--;
	}
	return (ptr);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
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
