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

static t_token	*not_frst_char(char c, t_lexeme *lx, t_dyn_arr *env, size_t i)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if ((ft_isspace(c) || !c) || (c == LIT_QUOTE || c == LIT_DOUBLE_QUOTE) \
			|| (c == *LIT_REDIR_OUT || c == *LIT_REDIR_IN || c == *LIT_PIPE))
	{
		*t = (t_token){.literal = false, .s = get_normal(lx, i, env)};
		return (t);
	}
	free(t);
	return (NULL);
}

static t_token	*lexical_a(char c, t_lexeme *lx, t_dyn_arr *env, size_t i)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (i == 0)
	{
		if (c == *LIT_REDIR_OUT || c == *LIT_REDIR_IN || c == *LIT_PIPE)
		{
			*t = (t_token){.literal = false, .s = get_operator(lx)};
			return (t);
		}
		else if (c == LIT_QUOTE || c == LIT_DOUBLE_QUOTE)
		{
			*t = (t_token){.literal = true, .s = get_string(lx, i, env)};
			return (t);
		}
	}
	free(t);
	return (not_frst_char(c, lx, env, i));
}

t_token	*get_token(t_dyn_arr *env, t_lexeme *lx)
{
	t_token	*t;
	size_t	i;
	char	c;

	i = 0;
	while (*get_char(lx, i) && ft_isspace(*get_char(lx, i)))
		++lx->input;
	while (*lx->input)
	{
		t = NULL;
		c = *get_char(lx, i);
		t = lexical_a(c, lx, env, i);
		if (t)
			return (t);
		i++;
	}
	return (NULL);
}
