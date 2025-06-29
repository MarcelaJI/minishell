/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:26:22 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/29 11:24:27 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_input(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->in_fds)
		free(data->in_fds);
	if (data->out_fds)
		free(data->out_fds);
	if (data->pids)
		free(data->pids);
	freelist(data->tokens);
	if (data->instructions)
		free_str_array(data->instructions, data->cmd_count);
	data->cmd_count = 0;
	data->prev_pipe_fd = -1;
	data->open_fail = 0;
	data->input = NULL;
	data->tokens = NULL;
	data->instructions = NULL;
	data->in_fds = NULL;
	data->out_fds = NULL;
	data->pids = NULL;
}

void	take_input(t_data *data)
{
	while (1)
	{
		signal(SIGINT, readline_sig);
		signal(SIGQUIT, SIG_IGN);
		data->input = readline(SHELLPRMPT);
		if (exit_nbr == SIGINT)
			data->exit_status = 1;
		exit_nbr = -1;
		if (!data->input)
			break ;
		if (!parse_input(data))
		{
			alloc_fd_pid_arrays(data);
			if (data->cmd_count == 1 && is_builtin(data, 0))
				exec_single_builtin(data);
			else
				execution(data);
		}
		reset_input(data);
	}
}