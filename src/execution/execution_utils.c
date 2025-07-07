/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:24:26 by iranieri          #+#    #+#             */
/*   Updated: 2025/07/07 14:47:09 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_cmd_count(t_data *data)
{
	t_dlist	*temp;

	data->cmd_count = 1;
	temp = data->tokens;
	while (temp)
	{
		if (temp->token == PIPE)
			data->cmd_count++;
		temp = temp->next;
	}
}

char	**create_exec_array(t_data *data, int n)
{
	t_dlist	*temp;
	size_t	i;
	char	**exec_arr;

	i = 0;
	temp = skip_instructions(data->tokens, n);
	while (temp && temp->token != PIPE)
	{
		if ((temp->token == CMD || temp->token == PARAM) && temp->str)
			i++;
		temp = temp->next;
	}
	exec_arr = ft_calloc(i + 1, sizeof(char *));
	check_memory_failure(data, NULL, exec_arr, 2);
	i = 0;
	temp = skip_instructions(data->tokens, n);
	while (temp && temp->token != PIPE)
	{
		if ((temp->token == CMD || temp->token == PARAM) && temp->str)
			exec_arr[i++] = ms_strdup(temp->str, data);
		temp = temp->next;
	}
	return (exec_arr);
}

void	convert_tokens(t_data *data)
{
	t_dlist	*temp;
	int		i;

	set_cmd_count(data);
	temp = data->tokens;
	data->instructions = ft_calloc(sizeof(char *), (data->cmd_count + 1));
	check_memory_failure(data, NULL, data->instructions, 2);
	i = 0;
	while (i < data->cmd_count)
	{
		if (temp && temp->token == PIPE)
			temp = temp->next;
		while (temp && temp->token != PIPE)
		{
			if ((temp->token == CMD || temp->token == PARAM) && temp->str)
				data->instructions[i] = ms_strjoin(data->instructions[i],
						temp->str, 1, data);
			if ((temp->token == CMD || temp->token == PARAM) && temp->str)
				data->instructions[i] = ms_strjoin(data->instructions[i], " ",
						1, data);
			temp = temp->next;
		}
		i++;
	}
}

void	exit_status(pid_t pid, t_data *data)
{
	pid_t			temp;
	int				status;
	int				last_status;
	int				sig_exit;
	t_status_info	info;

	last_status = 0;
	sig_exit = 0;
	info.last_status = &last_status;
	info.sig_exit = &sig_exit;
	while (1)
	{
		temp = wait(&status);
		if (temp <= 0)
			break ;
		handle_process_status(temp, pid, status, &info);
	}
	if (sig_exit)
		data->exit_status = sig_exit;
	else
		data->exit_status = last_status;
}

void	handle_process_status(pid_t temp, pid_t pid, int status,
			t_status_info *info)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit", 2);
		else if (sig == SIGINT)
			ft_putchar_fd('\n', 2);
		*(info->sig_exit) = 128 + sig;
	}
	if (temp == pid)
	{
		if (WIFEXITED(status))
			*(info->last_status) = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*(info->last_status) = 128 + WTERMSIG(status);
	}
}
