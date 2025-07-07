/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:39:36 by ingjimen          #+#    #+#             */
/*   Updated: 2025/07/07 14:25:03 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_nbr;

void	reset_data(t_data *data)
{
	g_exit_nbr = -1;
	data->input = NULL;
	data->instructions = NULL;
	data->tokens = NULL;
	data->env = NULL;
	data->in_fds = NULL;
	data->out_fds = NULL;
	data->pids = NULL;
	data->exit_status = 0;
	data->cmd_count = 0;
	data->prev_pipe_fd = -1;
	data->open_fail = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (1);
	(void)av;
	reset_data(&data);
	create_env(&data, env);
	if (!isatty(0))
		rl_outstream = stdin;
	take_input(&data);
	free_all(&data);
}
