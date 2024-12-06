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
