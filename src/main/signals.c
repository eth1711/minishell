/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:50:58 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/20 18:14:58 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int sigint, siginfo_t *info, void *data)
{
	(void)sigint;
	(void)data;
	(void)info;
}

void	handle_sigint(int sigint, siginfo_t *info, void *data)
{
	(void)sigint;
	(void)data;
	(void)info;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}

void	init_signals(void)
{
	struct sigaction sa;
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_sigint;
	sigaction(CTRL_C, &sa, 0);
	sa.sa_sigaction = handle_sigquit;
	sigaction(CTRL_SLSH, &sa, 0);
	
}
