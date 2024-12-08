#include "../ms.h"

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
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

int	ft_isnumber(char *str)
{
	int i;

	if (str[0] == '\0')
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
