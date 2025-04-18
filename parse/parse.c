/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:07:12 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:07:14 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	parse(t_dyn_arr *tokens, t_terminal *terminal)
{
	ft_set_tktype((t_token **)tokens->buf);
	ft_set_subtype((t_token **)tokens->buf);
	if (ft_get_synt_err((t_token **)tokens->buf))
	{
		ft_free_tokens(tokens);
		return (1);
	}
	terminal->commands = ft_get_cmds((t_token **)tokens->buf);
	ft_free_tokens(tokens);
	return (0);
}

t_tk_subtype	ft_get_wrd_subtype(t_token **input, int i)
{
	const t_token		*prev = input[i - 1];
	const t_tk_subtype	prev_st = prev->type.sub_tk;

	if (prev && (prev->type.main_tk == TK_COMMAND \
				|| prev_st == TK_ARG))
		return (TK_ARG);
	else if (prev && prev->type.main_tk == TK_OPERATOR \
			&& !input[i]->type.sub_tk)
	{
		if (prev_st == TK_REDIR_APP || prev_st == TK_REDIR_OUT \
				|| prev_st == TK_REDIR_IN)
			return (TK_FILENAME);
		else if (prev_st == TK_REDIR_HERE)
			return (TK_EOF);
	}
	return (TK_NONE);
}

int	ft_is_operator(const char *str)
{
	int			i;
	const char	*operators[] = {"&&", "||", ";;",
		"<<", ">>", "<&", ">&", "<>", "<<-", ">|",
		"|", "&", ";", "(", ")", "{", "}", "!",
		"<", ">", NULL};

	i = 0;
	while (operators[i] != NULL)
	{
		if (ft_strcmp((char *)str, operators[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_set_tktype(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_is_operator(tokens[i]->s) && !tokens[i]->literal)
			tokens[i++]->type.main_tk = TK_OPERATOR;
		else if ((i > 0 && !ft_strcmp(tokens[i - 1]->s, "|") \
					&& !tokens[i - 1]->literal) || (i == 0))
		{
			tokens[i++]->type.main_tk = TK_COMMAND;
			while (tokens[i] && !ft_is_operator(tokens[i]->s))
				tokens[i++]->type.main_tk = TK_WORD;
		}
		else
			tokens[i++]->type.main_tk = TK_WORD;
	}
}

int	ft_is_builtin(char *s)
{
	int			i;
	const char	**builtins;

	builtins = (const char *[]){"echo", "pwd", "cd", "export", "unset", \
		"env", "exit", NULL};
	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(s, builtins[i++]))
			return (1);
	}
	return (0);
}
