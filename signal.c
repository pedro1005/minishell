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

void	set_heredoc_sig()
{
	signal(SIGINT, handle_heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc_sig(int signbr)
{
	if (signbr == SIGINT)
		exit(130);
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