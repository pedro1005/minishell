#include "../ms.h"

//ver onde get_var_name melhor se encaixa
char	*get_var_name(char *var)
{
	size_t	i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i += 1;
	name = (char *)malloc((sizeof(char) * i) + 1);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		name[i] = var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_var_value(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i += 1;
	i += 1;
	return (var + i);
}

//join next token with the current one if conditions are met
char	*join_next(t_lexer *lexer, const char *token, t_dyn_arr *env, \
		bool is_quoted)
{
	char	curr;
	char	*join;
	char	*tmp;
	t_token	*tmp_tk;

	curr = *get_char(lexer, 0);
	tmp_tk = NULL;
	if (curr && !ft_isspace(curr) && curr != '|' && curr != '<' && curr != '>'
		&& (curr == LIT_QUOTE || curr == LIT_DOUBLE_QUOTE || is_quoted))
	{
		tmp_tk = get_token(env, lexer);
		join = tmp_tk->s;
		tmp = (char *)token;
		token = ft_strjoin(token, join);
		free(tmp);
		free(join);
		free(tmp_tk);
	}
	if (ft_strcmp((char *)token, (const char *)("$")) == 0 && curr == '"')
	{
		token = ft_strdup("");
		get_char(lexer, -1);
	}
	return ((char *)token);
}
