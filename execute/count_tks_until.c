#include "../ms.h"

int	ft_count_tks_until_op(t_token **tokens, int *i)
{
	int	n;

	n = 1;
	while (tokens[*i] && tokens[*i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[*i]->type.sub_tk == TK_ARG)
			n++;
		(*i)++;
	}
	return (n);
}
