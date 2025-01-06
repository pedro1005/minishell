/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:07:53 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:07:55 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	free_dyn_arr(t_dyn_arr dy_arr)
{
	t_dyn_arr	temp;
	int			i;

	i = 0;
	temp = dy_arr;
	while (temp.buf && temp.buf[i])
	{
		free(temp.buf[i]);
		temp.buf[i] = NULL;
		i++;
	}
	free(temp.buf);
	temp.buf = NULL;
}

void	ft_free_tokens(t_dyn_arr *tokens)
{
	t_dyn_arr	*temp;
	t_token		**list;
	int			i;

	temp = tokens;
	list = (t_token **)temp->buf;
	i = 0;
	while (list[i])
	{
		free(list[i]->s);
		list[i]->s = NULL;
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
	free(tokens);
	tokens = NULL;
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}
