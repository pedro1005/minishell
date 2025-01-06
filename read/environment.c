/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:05:22 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:05:25 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*get_var_value(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i += 1;
	i += 1;
	return (var + i);
}

int	pos_env_var(t_dyn_arr *env, char *find)
{
	size_t	i;
	size_t	equal_sign;
	char	*env_var;
	char	*var_name;

	i = 0;
	equal_sign = 0;
	var_name = NULL;
	while (find[equal_sign] && find[equal_sign] != '=')
		equal_sign += 1;
	while (i < env->len)
	{
		env_var = env->buf[i];
		var_name = get_var_name(env_var);
		if (env_var && ft_strncmp(find, env_var, equal_sign) == 0
			&& (equal_sign == (ft_strlen(var_name))))
		{
			free(var_name);
			return (i);
		}
		if (var_name)
			free(var_name);
		i += 1;
	}
	return (-1);
}

void	update_shlvl(char *minishlvl, t_dyn_arr *env, int lvl)
{
	lvl = ft_atoi(minishlvl) + 1;
	free(minishlvl);
	minishlvl = ft_strjoin("MINISHLVL=", ft_itoa(lvl));
	ft_add_var(env, minishlvl);
	free(minishlvl);
}

t_dyn_arr	env_init(char **envp)
{
	size_t		i;
	t_dyn_arr	env;
	char		*minishlvl;
	int			lvl;

	minishlvl = NULL;
	lvl = 1;
	env = dyn_arr_new();
	i = 0;
	while (envp[i])
	{
		dyn_arr_push(&env, ft_strdup(envp[i]));
		i += 1;
	}
	dyn_arr_push(&env, NULL);
	minishlvl = ft_getenv(envp, "MINISHLVL");
	if (!minishlvl)
		ft_add_var(&env, "MINISHLVL=1");
	else
	{
		update_shlvl(minishlvl, &env, lvl);
	}
	return (env);
}
