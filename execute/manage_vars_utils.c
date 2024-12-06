#include "../ms.h"

char	*ft_get_clean_var_name(char *var)
{
	if (!var)
		return (NULL);
	if (ft_strchr((const char *)var, '='))
		return (get_var_name(var));
	return (ft_strdup(var));
}
