/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tks_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:54:27 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 18:54:31 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	ft_count_tks_until_op(t_token **tokens, int *i)
{
	int	n;

	n = 1;
	while (tokens[*i] && tokens[*i]->type.sub_tk != TK_PIPE)
	{
		if (tokens[*i]->type.sub_tk == TK_ARG)
			n++;
		(*i)++;
	}
	return (n);
}
