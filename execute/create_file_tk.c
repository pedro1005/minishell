#include "../ms.h"

t_token	*create_file_token(t_token *current, t_token *previous)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->s = ft_strdup(current->s);
	new_token->type = previous->type;
	new_token->literal = current->literal;
	return (new_token);
}
