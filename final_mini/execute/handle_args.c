/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:01:43 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:01:45 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

void	ft_fill_args_loop(char **args, t_token **tokens, int *i, int *j)
{
	args[*j] = ft_strdup(tokens[*i]->s);
	(*i)++;
	(*j)++;
	while (tokens[*i] && tokens[*i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[*i]->type.sub_tk == TK_ARG)
		{
			args[*j] = ft_strdup(tokens[*i]->s);
			(*j)++;
		}
		(*i)++;
	}
}

void	ft_fill_args(char **args, t_token **tokens, int index)
{
	int	i;
	int	j;

	i = index;
	j = 0;
	ft_fill_args_loop(args, tokens, &i, &j);
	ft_handle_redirections(args, tokens, &i, &j);
	args[j] = NULL;
}

int	ft_count_redir_args(t_token **tokens, int *i)
{
	int	n;

	n = 0;
	while (tokens[*i] && tokens[*i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[*i]->type.sub_tk == TK_REDIR_APP \
				|| tokens[*i]->type.sub_tk == TK_REDIR_OUT)
		{
			*i += 2;
			while (tokens[*i] && tokens[*i]->type.main_tk != TK_OPERATOR)
			{
				n++;
				(*i)++;
			}
		}
		else
			(*i)++;
	}
	return (n);
}

int	ft_get_n_rdrargs(t_token **tokens, int index)
{
	int	i;
	int	n;

	i = index;
	n = 0;
	n += ft_count_tks_until_op(tokens, &i);
	n += ft_count_redir_args(tokens, &i);
	return (n);
}

char	**ft_get_rdrexargs(t_token **tokens, int index)
{
	char		**args;
	const int	n_args = ft_get_n_rdrargs(tokens, index);

	if (!n_args)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (n_args + 1));
	if (!args)
		return (NULL);
	ft_fill_args(args, tokens, index);
	return (args);
}
