#include "../ms.h"

t_redir	*ft_init_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	memset(redir, 0, sizeof(t_redir));
	return (redir);
}

int	ft_find_redir_start(t_token **tokens, int index)
{
	int	i;

	i = index;
	if (i > 0)
		i++;
	while (1)
	{
		if (!tokens[i] || tokens[i]->type.sub_tk == TK_PIPE)
			return (-1);
		if (tokens[i]->type.main_tk == TK_OPERATOR \
				&& tokens[i]->type.sub_tk != TK_PIPE)
			break ;
		i++;
	}
	return (i);
}

void	ft_populate_redir(t_redir *redir, t_token **tokens, int index)
{
	redir->args_in = ft_get_args_i(tokens, index);
	redir->args_out = ft_get_args_o(tokens, index);
	ft_set_redir_type(redir, tokens, index);
	if (redir->type_in.sub_tk && redir->type_in.sub_tk == TK_REDIR_HERE)
		redir->delim = ft_get_delim(tokens, index);
	redir->exec = ft_get_redir_ex(tokens, index);
}

t_redir	*ft_get_redir(t_token **tokens, int index)
{
	int		start_index;
	t_redir	*redir;

	start_index = ft_find_redir_start(tokens, index);
	if (start_index == -1 || !tokens[start_index])
		return (NULL);
	redir = ft_init_redir();
	start_index = index;
	if (start_index > 0)
        	start_index++;
	ft_populate_redir(redir, tokens, start_index);
	return (redir);
}
