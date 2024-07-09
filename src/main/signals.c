/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:50:58 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/09 17:24:54 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int sigint, siginfo_t *info, void *data)
{
	(void)sigint;
	(void)data;
	(void)info;
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int sigint, siginfo_t *info, void *data)
{
	(void)sigint;
	(void)data;
	(void)info;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	term_ios(void)
{
	struct termios	t_ios;

	tcgetattr(0, &t_ios);
	t_ios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &t_ios);
}

void	init_signals(void)
{
	struct sigaction	sa;

	term_ios();
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_sigint;
	sigaction(CTRL_C, &sa, 0);
	sa.sa_sigaction = handle_sigquit;
	sigaction(CTRL_SLSH, &sa, 0);
}
