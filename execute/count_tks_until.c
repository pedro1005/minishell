#include "../ms.h"

int	ft_count_tks_until_op(t_token **tokens, int *i)
{
	int	n;

	n = 1; //n=0
	//while (tokens[*i] && tokens[*i]->type.main_tk != TK_OPERATOR)
	while (tokens[*i] && tokens[*i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[*i]->type.sub_tk == TK_ARG) //+
			n++;
		(*i)++;
	}
	return (n);
}
