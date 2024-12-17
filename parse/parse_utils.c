/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:07:22 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:07:24 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (tokens[i]->type.main_tk == TK_WORD
			&& tokens[i]->type.sub_tk == TK_NONE)
			tokens[i]->type.sub_tk = TK_ARG;
		i++;
	}
}

t_tk_subtype	ft_get_op_subtype(const char *input)
{
	int				i;
	const t_op_type	subtypes[] = {
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
			return (subtypes[i].type);
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

int	ft_check_quote_error(char *in)
{
	int		get_error;
	int		i;
	char	quote;

	i = 0;
	get_error = 0;
	while (in && in[i])
	{
		if (in[i] == '\'' || in[i] == '"')
		{
			quote = in[i++];
			get_error = 1;
			while (in[i] && in[i] != quote)
				i++;
			if (in[i] == quote)
			{
				get_error = 0;
				i++;
			}
		}
		else
			i++;
	}
	return (get_error);
}
