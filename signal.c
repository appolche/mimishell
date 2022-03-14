#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	par_set_default_sig()
{
	signal(SIGINT, data.SIG_INT);
	signal(SIGQUIT, data.SIG_QUIT);
}

void	par_set_custom_sig(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	par_disable_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_init()
{
	rl_catch_signals = 0;
	data.SIG_INT = signal(SIGINT, signal_handler);
	data.SIG_QUIT = signal(SIGQUIT, SIG_IGN);
}
