/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:58:56 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:58:58 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	ft_redir_has_cmd(t_token **tokens, int index)
{
	int	i;

	i = index;
	if (tokens[i] && tokens[i]->type.main_tk != TK_OPERATOR)
		return (1);
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[i]->type.sub_tk == TK_REDIR_APP \
				|| tokens[i]->type.sub_tk == TK_REDIR_OUT)
		{
			i = i + 2;
			if (tokens[i] && tokens[i]->type.main_tk != TK_OPERATOR)
				return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_get_rdrexname(t_token **tokens, int index)
{
	int		i;
	char	*name;

	i = index;
	name = NULL;
	if (tokens[i] && tokens[i]->type.main_tk != TK_OPERATOR)
	{
		name = ft_strdup(tokens[i]->s);
		return (name);
	}
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[i]->type.sub_tk == TK_REDIR_APP \
				|| tokens[i]->type.sub_tk == TK_REDIR_OUT)
		{
			i = i + 2;
			if (tokens[i] && tokens[i]->type.main_tk != TK_OPERATOR)
			{
				name = ft_strdup(tokens[i]->s);
				return (name);
			}
		}
		i++;
	}
	return (name);
}

t_exec	*ft_get_redir_ex(t_token **tokens, int index)
{
	t_exec	*exec;
	int		i;

	i = index;
	if (ft_redir_has_cmd(tokens, index))
		exec = (t_exec *)malloc(sizeof(t_exec));
	else
		return (NULL);
	memset(exec, 0, sizeof(t_exec));
	exec->name = ft_get_rdrexname(tokens, i);
	exec->args = ft_get_rdrexargs(tokens, i);
	exec->type.main_tk = TK_COMMAND;
	if (exec->args)
		exec->type.sub_tk = ft_get_cmd_subtype((const char *)exec->args[0]);
	return (exec);
}
