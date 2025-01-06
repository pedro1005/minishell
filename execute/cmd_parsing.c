/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:59:17 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:59:19 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

t_exec	*ft_get_exec_r(t_token **tokens, int index)
{
	t_exec	*exec;
	int		i;

	i = index;
	while (tokens[i] && tokens[i]->type.main_tk != TK_COMMAND)
		i++;
	if (!tokens[i] || tokens[i]->type.main_tk != TK_COMMAND)
		return (NULL);
	exec = (t_exec *)malloc(sizeof(t_exec));
	ft_memset(exec, 0, sizeof(t_exec));
	exec->type = tokens[i]->type;
	exec->name = ft_strdup(tokens[i]->s);
	exec->args = ft_get_args(tokens, i);
	return (exec);
}

t_exec	*ft_get_exec_l(t_token **tokens, int index)
{
	t_exec	*exec;
	int		i;

	i = index;
	while (i >= 0 && tokens[i]->type.main_tk != TK_COMMAND)
	{
		if (tokens[i]->type.sub_tk == TK_PIPE)
			return (NULL);
		i--;
	}
	if (tokens[i]->type.main_tk != TK_COMMAND)
		return (NULL);
	exec = (t_exec *)malloc(sizeof(t_exec));
	ft_memset(exec, 0, sizeof(t_exec));
	exec->type = tokens[i]->type;
	exec->name = ft_strdup(tokens[i]->s);
	exec->args = ft_get_args(tokens, i);
	return (exec);
}

//get_redir() helper
int	ft_get_n_args(t_token **tokens, int index)
{
	int	i;
	int	n;

	i = index;
	n = 0;
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[i]->type.sub_tk == TK_REDIR_IN)
		{
			i++;
			while (tokens[i] && tokens[i]->type.main_tk == TK_WORD)
			{
				n++;
				i++;
			}
		}
		else
			i++;
	}
	return (n);
}

//get_redir() helper
char	**ft_get_args_i(t_token **tokens, int index)
{
	char		**files;
	int			i;
	int			j;

	i = index;
	j = 0;
	if (!ft_get_n_args(tokens, index))
		return (NULL);
	files = (char **)malloc(sizeof(char *)
			* (ft_get_n_args(tokens, index) + 1));
	if (!files)
		return (NULL);
	while (tokens[i] && tokens[i]->type.sub_tk != TK_PIPE)
	{
		i++;
		if (tokens[i - 1]->type.sub_tk == TK_REDIR_IN)
		{
			while (tokens[i]
				&& tokens[i]->type.main_tk == TK_WORD
				&& tokens[i]->type.sub_tk == TK_FILENAME)
				files[j++] = ft_strdup(tokens[i++]->s);
		}
	}
	files[j] = NULL;
	return (files);
}
