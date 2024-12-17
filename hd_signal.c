/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:22 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:04:33 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	handle_heredoc_sig(int signbr)
{
	if (signbr == SIGINT)
		exit(130);
}

void	set_heredoc_sig(void)
{
	signal(SIGINT, handle_heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
}
