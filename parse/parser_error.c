/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:56:06 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:56:10 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	synt_err_msg(char *token)
{
	g_signals = 2;
	write(2, "syntax error near unexpected token `", 36);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	return (1);
}

int	ft_get_synt_err(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (!tokens[i + 1] && tokens[i]->type.sub_tk == TK_PIPE)
			return (synt_err_msg(tokens[i]->s));
		else if (!tokens[i + 1] && tokens[i]->type.main_tk == TK_OPERATOR)
			return (synt_err_msg("newline"));
		if (tokens[i + 1] && ((tokens[i]->type.sub_tk == TK_PIPE
					&& tokens[i + 1]->type.sub_tk == TK_PIPE)))
			return (synt_err_msg(tokens[i + 1]->s));
		i++;
	}
	return (0);
}
