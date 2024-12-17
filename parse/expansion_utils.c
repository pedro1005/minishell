/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:05:55 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:05:57 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

static bool	is_last_status(char *arg)
{
	while (arg && *arg != '$')
		arg++;
	return (ft_strncmp("$?", arg, 2) == 0);
}

char	*replace_var(const char *s, const char *sub, const char *with)
{
	size_t	new_len;
	size_t	delta;
	char	*buf;
	char	*rem;

	new_len = ft_strlen(s) - ft_strlen(sub) + ft_strlen(with);
	delta = ft_strnstr(s, sub, ft_strlen(s)) - s;
	buf = malloc(sizeof(char) * (new_len + 1));
	rem = ft_strnstr(s, sub, ft_strlen(s)) + ft_strlen(sub);
	ft_memcpy(buf, s, delta);
	ft_memcpy(buf + delta, with, ft_strlen(with));
	ft_memcpy(buf + delta + ft_strlen(with), rem, ft_strlen(rem));
	buf[new_len] = 0;
	return (buf);
}

char	*help_expand(char *buf, t_dyn_arr *env, char *var)
{
	char	*l_status;
	char	*var_value;

	if (is_last_status(buf))
	{
		l_status = ft_itoa(g_signals);
		buf = replace_var(buf, var, l_status);
		free(l_status);
	}
	else if (pos_env_var(env, var + 1) != -1)
	{
		var_value = get_var_value(env->buf[pos_env_var(env, var + 1)]);
		buf = replace_var(buf, var, var_value);
	}
	else
		buf = replace_var(buf, var, "");
	return (buf);
}
