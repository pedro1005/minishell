#include "../ms.h"

int	ft_var_exist(char **env, char *var)
{
	int		i;
	char	*var_name;
	char	*env_var;

	var_name = ft_get_clean_var_name(var);
	if (!var_name)
		return (0);
	i = 0;
	while (env[i])
	{
		env_var = get_var_name(env[i]);
		if (ft_strcmp(env_var, var_name) == 0)
		{
			free(env_var);
			free(var_name);
			return (1);
		}
		free(env_var);
		env_var = NULL;
		i++;
	}
	free(var_name);
	return (0);
}

char	**ft_allocate_env_buffer(t_dyn_arr *envp, int var_exist)
{
	char	**buf;

	if (var_exist)
    {
		buf = (char **)malloc(sizeof(char *) * (envp->len + 1));
	    memset(buf, 0, sizeof(char *) * (envp->len + 1));
    }
    else
    {
		buf = (char **)malloc(sizeof(char *) * (envp->len + 2));
        memset(buf, 0, sizeof(char *) * (envp->len + 2));
    }
    return (buf);
}

char	**ft_copy_env_with_var(t_dyn_arr *envp, char *var, int var_exist)
{
	char	**buf;
	int		i;
	char	*temp;
	char	*new_var;

	new_var = get_var_name(var);
	buf = ft_allocate_env_buffer(envp, var_exist);
	if (!buf || !new_var)
		return (NULL);
	i = 0;
	while ((char *)envp->buf[i])
	{
		temp = get_var_name((char *)envp->buf[i]);
		if (ft_strcmp(temp, (const char *)new_var) != 0)
			buf[i] = ft_strdup((const char *)envp->buf[i]);
		else
			buf[i] = ft_strdup((const char *)var);
		free(envp->buf[i++]);
		free(temp);
	}
	if (!var_exist)
		buf[i++] = ft_strdup((const char *)var);
	buf[i] = NULL;
	free(new_var);
	return (buf);
}

void	ft_add_var(t_dyn_arr *envp, char *var)
{
	int		var_exist;
	char	**new_buf;

	var_exist = ft_var_exist((char **)envp->buf, var);
	new_buf = ft_copy_env_with_var(envp, var, var_exist);
	if (!new_buf)
		return ;
	if (!var_exist)
		envp->len++;
	free(envp->buf);
	envp->buf = (void **)new_buf;
}

char	*ft_vardup(char **env, char *var_name)
{
	char	*dup;
	int		i;
	char	*env_name;

	if (!var_name)
		return (NULL);
	i = 0;
	dup = NULL;
	while (env[i])
	{
		env_name = get_var_name(env[i]);
		if (ft_strcmp(env_name, (const char *)var_name) == 0)
		{
			dup = ft_strdup((const char *)env[i]);
			free(env_name);
			return (dup);
		}
		free(env_name);
		i++;
	}
	return (dup);
}
