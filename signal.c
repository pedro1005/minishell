/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:06:25 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:06:27 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	handle_sig(int signbr);
void	handle_child_sig(int signbr);
void	handle_heredoc_sig(int signbr);

void	set_signal(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_sig(void)
{
	signal(SIGINT, handle_child_sig);
	signal(SIGQUIT, handle_child_sig);
}

void	handle_sig(int signbr)
{
	if (signbr == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signals = 130;
	}
}

void	handle_child_sig(int signbr)
{
	if (signbr == SIGQUIT)
	{
		write(2, "Quit(core dumped)\n", 17);
		write(1, "\n", 1);
		rl_on_new_line();
		g_signals = 131;
	}
	else if (signbr == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		g_signals = 130;
	}
}
