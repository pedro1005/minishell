/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:05:40 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:05:41 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	*get_normal(t_lexer *lexer, size_t i, t_dyn_arr *env)
{
	char	*token;

	token = ft_substr(lexer->input, 0, i);
	lexer->input += i;
	if (!lexer->is_heredoc)
		return (join_next(lexer, expand_token(token, env), env, false));
	else
	{
		lexer->is_heredoc = false;
		return (join_next(lexer, token, env, false));
	}
}

char	*get_string(t_lexer *lexer, size_t i, t_dyn_arr *env)
{
	char	*token;
	char	delim;
	char	*start;
	char	*end;
	size_t	delta;

	start = get_char(lexer, i);
	delim = *start;
	end = ft_strchr(start + 1, delim);
	if (!end)
	{
		printf("Unended quote/dquote\n");
		exit(EXIT_FAILURE);
	}
	delta = end - start;
	token = ft_substr(lexer->input, 1, delta - 1);
	lexer->input += delta + 1;
	if (delim == LIT_DOUBLE_QUOTE && !lexer->is_heredoc)
		return (join_next(lexer, expand_token(token, env), env, true));
	else
	{
		lexer->is_heredoc = false;
		return (join_next(lexer, token, env, true));
	}
}

char	*get_operator(t_lexer *lexer)
{
	char	*token;
	size_t	n;

	if (ft_strnstr(lexer->input, LIT_REDIR_DEL, sizeof(LIT_REDIR_DEL) - 1))
		lexer->is_heredoc = true;
	if (ft_strnstr(lexer->input, LIT_REDIR_APPEND, \
				sizeof(LIT_REDIR_APPEND) - 1) \
			|| ft_strnstr(lexer->input, LIT_REDIR_DEL, \
				sizeof(LIT_REDIR_DEL) - 1))
		n = sizeof(LIT_REDIR_APPEND) - 1;
	else if (ft_strnstr(lexer->input, LIT_PIPE, sizeof(LIT_PIPE) - 1) \
			|| ft_strnstr(lexer->input, LIT_REDIR_OUT, \
				sizeof(LIT_REDIR_OUT) - 1) || ft_strnstr(lexer->input, \
				LIT_REDIR_IN, sizeof(LIT_REDIR_IN) - 1))
		n = sizeof(LIT_PIPE) - 1;
	else
	{
		printf("Invalid operator\n");
		exit(EXIT_FAILURE);
	}
	token = ft_substr(lexer->input, 0, n);
	lexer->input += n;
	return (token);
}
