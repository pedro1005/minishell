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

t_terminal	*get_terminal(t_terminal *new)
{
	static t_terminal	*t = NULL;

	if (new)
		t = new;
	return (t);
}

void	handle_heredoc_sig(int sig)
{
	t_terminal	*t;

	if (sig == SIGINT)
	{
		t = get_terminal(NULL);
		write(1, "\n", 1);
		g_signals = 130;
		ft_free_cmds(t);
		free_dyn_arr(t->envp);
		free_dyn_arr(t->envt);
		exit(130);
	}
}

void	set_heredoc_sig(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_heredoc_sig;
	sigaction(SIGINT, &sa, NULL);
}
