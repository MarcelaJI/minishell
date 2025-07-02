/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:26:22 by ingjimen          #+#    #+#             */
/*   Updated: 2025/07/02 09:47:49 by ingjimen         ###   ########.fr       */
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

static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*get_dynamic_prompt(void)
{
	char	cwd[1024];
	char	*prompt;
	char	*tmp;

	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(CYAN "/unknown/shellmi>" RESET));
	tmp = ft_strjoin(CYAN, cwd);
	if (!tmp)
		return (ft_strdup(CYAN "/error/shellmi>" RESET));
	prompt = join_and_free(tmp, SHELL_SUFFIX);
	if (!prompt)
		return (ft_strdup(CYAN "/error/shellmi>" RESET));
	tmp = join_and_free(prompt, RESET);
	if (!tmp)
		return (ft_strdup(CYAN "/error/shellmi>" RESET));
	return (tmp);
}

void	take_input(t_data *data)
{
	char	*prompt;

	signal(SIGINT, readline_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = get_dynamic_prompt();
		data->input = readline(prompt);
		free(prompt);
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
