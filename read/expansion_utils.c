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
