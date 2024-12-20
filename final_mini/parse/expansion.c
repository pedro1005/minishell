/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:05:30 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:05:32 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*exp_var(const char *s, size_t i)
{
	size_t	j;

	if (s[i + 1] && s[i + 1] == '?')
		return (ft_substr(s, i, 2));
	else
	{
		j = 0;
		while (s[i + j + 1] && !ft_isspace(s[i + j + 1])
			&& s[i + j + 1] != '$'
			&& s[i + j + 1] != *LIT_REDIR_OUT
			&& s[i + j + 1] != *LIT_REDIR_IN
			&& s[i + j + 1] != *LIT_PIPE
			&& s[i + j + 1] != LIT_QUOTE
			&& s[i + j + 1] != LIT_DOUBLE_QUOTE)
			j += 1;
		if (j)
			return (ft_substr(s, i, j + 1));
	}
	return (NULL);
}

char	*dollar_sign(const char *s)
{
	size_t	i;
	char	*res;

	i = 0;
	res = NULL;
	while (i < ft_strlen(s))
	{
		if (s[i] == '$')
		{
			res = exp_var(s, i);
			if (res)
				return (res);
		}
		i += 1;
	}
	return (NULL);
}

char	*expand_token(const char *token, t_dyn_arr *env)
{
	char	*var;
	char	*buf;
	char	*tmp;

	buf = (char *)token;
	while (true)
	{
		var = dollar_sign(buf);
		if (!var)
			break ;
		tmp = buf;
		buf = help_expand(buf, env, var);
		free(tmp);
		free(var);
	}
	return (buf);
}
