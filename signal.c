/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:17:06 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/18 20:17:11 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	set_default_sig(void)
{
	signal(SIGINT, g_data.sig_int);
	signal(SIGQUIT, g_data.sig_quit);
}

void	set_custom_sig(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	disable_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_init(void)
{
	rl_catch_signals = 0;
	g_data.sig_int = signal(SIGINT, signal_handler);
	g_data.sig_quit = signal(SIGQUIT, SIG_IGN);
}
