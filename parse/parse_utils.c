#include "../ms.h"

void	ft_set_subtype(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type.main_tk == TK_COMMAND)
			tokens[i]->type.sub_tk = ft_get_cmd_subtype(tokens[i]->s);
		else if (tokens[i]->type.main_tk == TK_OPERATOR)
			tokens[i]->type.sub_tk = ft_get_op_subtype(tokens[i]->s);
		else if (tokens[i]->type.main_tk == TK_WORD)
			tokens[i]->type.sub_tk = ft_get_wrd_subtype(tokens, i);
		if (tokens[i]->type.main_tk == TK_WORD && tokens[i]->type.sub_tk == TK_NONE)	//+
			tokens[i]->type.sub_tk = TK_ARG;												//+
		i++;
	}
}

t_tk_subtype	ft_get_op_subtype(const char *input)
{
	int	i;
	static const struct {
		t_tk_subtype subtype;
		const char *symbol;
	} subtypes[] = {
		{TK_PIPE, "|"},
		{TK_REDIR_IN, "<"},
		{TK_REDIR_OUT, ">"},
		{TK_REDIR_APP, ">>"},
		{TK_REDIR_HERE, "<<"},
		{TK_NONE, NULL}
	};

	i = 0;
	while (subtypes[i].symbol != NULL)
	{
		if (ft_strcmp((char *)subtypes[i].symbol, input) == 0)
			return (subtypes[i].subtype);
		i++;
	}
	return (TK_NONE);
}

t_tk_subtype	ft_get_cmd_subtype(const char *input)
{
	if (ft_is_builtin((char *)input))
		return (TK_BUILT_IN);
	else if (input[0] == '/' || input[0] == '.')
		return (TK_PATH);
	else if (ft_strchr(input, '='))
		return (TK_EQL);
	return (TK_EXEC);
}
