/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:59:38 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:59:44 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

void	ft_handle_redirections(char **args, t_token **tokens, int *i, int *j)
{
	while (tokens[*i] && tokens[*i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[*i]->type.sub_tk == TK_REDIR_APP \
				|| tokens[*i]->type.sub_tk == TK_REDIR_OUT)
		{
			*i += 2;
			ft_fill_args_loop(args, tokens, i, j);
		}
		else
			(*i)++;
	}
}

int	ft_get_n_files(t_token **tokens, int index)
{
	int	n;
	int	i;

	n = 0;
	i = index;
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[i]->type.sub_tk == TK_REDIR_APP \
				|| tokens[i]->type.sub_tk == TK_REDIR_OUT)
		{
			i++;
			if (tokens[i] && tokens[i]->type.main_tk == TK_WORD)
				n++;
		}
		else
			i++;
	}
	return (n);
}

void	process_redirection(t_token **files, t_token **tokens, int *i, int *j)
{
	if (tokens[*i] && tokens[*i]->type.main_tk == TK_WORD)
	{
		files[*j] = create_file_token(tokens[*i], tokens[*i - 1]);
		if (files[*j])
			(*j)++;
	}
	(*i)++;
}

t_token	**ft_get_args_o(t_token **tokens, int index)
{
	t_token		**files;
	int			n_files;
	int			i;
	int			j;

	i = index;
	j = 0;
	n_files = ft_get_n_files(tokens, index);
	files = (t_token **)malloc(sizeof(t_token *) * (n_files + 1));
	if (!files)
		return (NULL);
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[i]->type.sub_tk == TK_REDIR_APP \
				|| tokens[i]->type.sub_tk == TK_REDIR_OUT)
		{
			i++;
			process_redirection(files, tokens, &i, &j);
		}
		else
			i++;
	}
	files[j] = NULL;
	return (files);
}

void	ft_set_redir_type(t_redir *redir, t_token **tokens, int index)
{
	int	i;

	i = index;
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[i]->type.sub_tk == TK_REDIR_APP \
				|| tokens[i]->type.sub_tk == TK_REDIR_OUT)
			redir->type_out.sub_tk = tokens[i]->type.sub_tk;
		else if (tokens[i]->type.sub_tk == TK_REDIR_HERE \
				|| tokens[i]->type.sub_tk == TK_REDIR_IN)
			redir->type_in.sub_tk = tokens[i]->type.sub_tk;
		i++;
	}
}
