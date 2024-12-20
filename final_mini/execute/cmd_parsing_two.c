/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:53:07 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:53:11 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

t_tree	*ft_get_cmds(t_token **tokens)
{
	t_tree	*head;
	int		i;

	i = 0;
	head = (t_tree *)malloc(sizeof(t_tree));
	ft_memset(head, 0, sizeof(t_tree));
	head->redir = ft_get_redir(tokens, i);
	if (!head->redir)
		head->exec = ft_get_exec_r(tokens, i);
	head->right_tree = ft_get_pipe(tokens, &i);
	if (head->right_tree)
		head->right_tree->left_tree = head;
	return (head);
}

t_tree	*ft_get_pipe(t_token **tokens, int *index)
{
	t_tree	*new_tree;
	int		i;

	(*index)++;
	while (tokens[*index] && tokens[*index]->type.sub_tk != TK_PIPE)
		(*index)++;
	if (!tokens[*index] || tokens[*index]->type.sub_tk != TK_PIPE)
		return (NULL);
	new_tree = (t_tree *)malloc(sizeof(t_tree));
	ft_memset(new_tree, 0, sizeof(t_tree));
	i = *index;
	while (tokens[i])
	{
		new_tree->redir = ft_get_redir(tokens, i);
		if (!new_tree->redir)
			new_tree->exec = ft_get_exec_r(tokens, i);
		new_tree->right_tree = ft_get_pipe(tokens, &i);
		if (new_tree->right_tree)
			new_tree->right_tree->left_tree = new_tree;
	}
	*index = i;
	return (new_tree);
}

char	**fill_delim(int i, int index, t_token **tokens, int n_delim)
{
	char	**delim;

	delim = (char **)malloc(sizeof(char *) * (n_delim + 1));
	if (!delim)
		return (NULL);
	delim[n_delim] = NULL;
	n_delim--;
	while (i >= index && (n_delim >= 0))
	{
		if (tokens[i] && tokens[i]->type.sub_tk == TK_EOF)
		{
			delim[n_delim] = ft_strdup(tokens[i]->s);
			n_delim-- ;
		}
		i--;
	}
	return (delim);
}

//get_redir() helper
char	**ft_get_delim(t_token **tokens, int index)
{
	int		i;
	int		n_delim;
	char	**delim;

	i = index;
	delim = NULL;
	n_delim = 0;
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[i]->type.sub_tk == TK_EOF)
			n_delim++;
		i++;
	}
	delim = fill_delim(i, index, tokens, n_delim);
	return (delim);
}
