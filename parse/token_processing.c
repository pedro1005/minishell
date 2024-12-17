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

//join next token with the current one if conditions are met
char	*join_next(t_lexeme *lx, const char *token, t_dyn_arr *env, \
		bool is_quoted)
{
	char	curr;
	char	*join;
	char	*tmp;
	t_token	*tmp_tk;

	curr = *get_char(lx, 0);
	tmp_tk = NULL;
	if (curr && !ft_isspace(curr) && curr != '|' && curr != '<' && curr != '>'
		&& (curr == LIT_QUOTE || curr == LIT_DOUBLE_QUOTE || is_quoted))
	{
		tmp_tk = get_token(env, lx);
		join = tmp_tk->s;
		tmp = (char *)token;
		token = ft_strjoin(token, join);
		free(tmp);
		free(join);
		free(tmp_tk);
	}
	if (ft_strcmp((char *)token, (const char *)("$")) == 0 && curr == '"')
	{
		free((char *)token);
		token = ft_strdup("");
		get_char(lx, -1);
	}
	return ((char *)token);
}

char	*get_normal(t_lexeme *lx, size_t i, t_dyn_arr *env)
{
	char	*token;

	token = ft_substr(lx->input, 0, i);
	lx->input += i;
	if (!lx->has_heredoc)
		return (join_next(lx, expand_token(token, env), env, false));
	else
	{
		lx->has_heredoc = false;
		return (join_next(lx, token, env, false));
	}
}

char	*get_string(t_lexeme *lx, size_t i, t_dyn_arr *env)
{
	char	*token;
	char	delim;
	char	*start;
	char	*end;
	size_t	delta;

	start = get_char(lx, i);
	delim = *start;
	end = ft_strchr(start + 1, delim);
	if (!end)
	{
		printf("Unended quote/dquote\n");
		exit(EXIT_FAILURE);
	}
	delta = end - start;
	token = ft_substr(lx->input, 1, delta - 1);
	lx->input += delta + 1;
	if (delim == LIT_DOUBLE_QUOTE && !lx->has_heredoc)
		return (join_next(lx, expand_token(token, env), env, true));
	else
	{
		lx->has_heredoc = false;
		return (join_next(lx, token, env, true));
	}
}

char	*get_operator(t_lexeme *lx)
{
	char	*token;
	size_t	n;

	if (ft_strnstr(lx->input, LIT_REDIR_DEL, sizeof(LIT_REDIR_DEL) - 1))
		lx->has_heredoc = true;
	if (ft_strnstr(lx->input, LIT_REDIR_APPEND, \
				sizeof(LIT_REDIR_APPEND) - 1) \
			|| ft_strnstr(lx->input, LIT_REDIR_DEL, \
				sizeof(LIT_REDIR_DEL) - 1))
		n = sizeof(LIT_REDIR_APPEND) - 1;
	else if (ft_strnstr(lx->input, LIT_PIPE, sizeof(LIT_PIPE) - 1) \
			|| ft_strnstr(lx->input, LIT_REDIR_OUT, \
				sizeof(LIT_REDIR_OUT) - 1) || ft_strnstr(lx->input, \
				LIT_REDIR_IN, sizeof(LIT_REDIR_IN) - 1))
		n = sizeof(LIT_PIPE) - 1;
	else
	{
		printf("Invalid operator\n");
		exit(EXIT_FAILURE);
	}
	token = ft_substr(lx->input, 0, n);
	lx->input += n;
	return (token);
}
