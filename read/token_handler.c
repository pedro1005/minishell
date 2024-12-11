/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:06:03 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:06:05 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

static t_token	*not_frst_char(char c, t_lexer *lexer, t_dyn_arr *env, size_t i)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if ((ft_isspace(c) || !c) || (c == LIT_QUOTE || c == LIT_DOUBLE_QUOTE) \
			|| (c == *LIT_REDIR_OUT || c == *LIT_REDIR_IN || c == *LIT_PIPE))
	{
		*t = (t_token){.literal = false, .s = get_normal(lexer, i, env)};
		return (t);
	}
	free(t);
	return (NULL);
}

static t_token	*lexical_a(char c, t_lexer *lexer, t_dyn_arr *env, size_t i)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (i == 0)
	{
		if (c == *LIT_REDIR_OUT || c == *LIT_REDIR_IN || c == *LIT_PIPE)
		{
			*t = (t_token){.literal = false, .s = get_operator(lexer)};
			return (t);
		}
		else if (c == LIT_QUOTE || c == LIT_DOUBLE_QUOTE)
		{
			*t = (t_token){.literal = true, .s = get_string(lexer, i, env)};
			return (t);
		}
	}
	free(t);
	return (not_frst_char(c, lexer, env, i));
}

t_token	*get_token(t_dyn_arr *env, t_lexer *lexer)
{
	t_token	*t;
	size_t	i;
	char	c;

	i = 0;
	while (*get_char(lexer, i) && ft_isspace(*get_char(lexer, i)))
		++lexer->input;
	while (*lexer->input)
	{
		c = *get_char(lexer, i);
		t = lexical_a(c, lexer, env, i);
		if (t)
			return (t);
		i++;
	}
	return (NULL);
}
