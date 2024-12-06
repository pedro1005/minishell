#include "../ms.h"

int	pos_env_var(t_dyn_arr *env, char *find)
{
	size_t	i;
	size_t	equal_sign;
	char	*env_var;

	i = 0;
	equal_sign = 0;
	while (find[equal_sign] && find[equal_sign] != '=')
		equal_sign += 1;
	while (i < env->len)
	{
		env_var = env->buf[i];
		if (env_var && ft_strncmp(find, env_var, equal_sign) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

t_dyn_arr	env_init(char **envp)
{
	size_t		i;
	t_dyn_arr	env;

	env = dyn_arr_new();
	i = 0;
	while (envp[i])
	{
		dyn_arr_push(&env, ft_strdup(envp[i]));
		i += 1;
	}
	dyn_arr_push(&env, NULL);
	return (env);
}