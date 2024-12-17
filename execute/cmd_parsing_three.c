/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:23:13 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:23:38 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	count_args(t_token **tokens, int index, int *i)
{
	int	count;

	count = 0;
	*i = index + 1;
	while (tokens[*i] && tokens[*i]->type.sub_tk == TK_ARG)
	{
		count++;
		(*i)++;
	}
	return (count);
}

char	**ft_get_args(t_token **tokens, int index)
{
	int		n;
	int		i;
	int		j;
	char	**args;

	i = index + 1;
	j = 0;
	n = count_args(tokens, index, &i);
	if (n == 0)
		return (NULL);
	i = i - n - 1;
	n++;
	args = (char **)malloc(sizeof(char *) * (n + 2));
	if (!args)
		return (NULL);
	while (n > 0)
	{
		args[j++] = ft_strdup(tokens[i]->s);
		i++;
		n--;
	}
	args[j] = NULL;
	return (args);
}
