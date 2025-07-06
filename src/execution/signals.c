/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:38:11 by iranieri          #+#    #+#             */
/*   Updated: 2025/07/06 20:20:33 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_nbr = SIGINT;
		close(STDIN_FILENO);
	}
}

void	do_nothing(int sig)
{
	g_exit_nbr = sig;
}

void	readline_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_nbr = SIGINT;
	}
}
