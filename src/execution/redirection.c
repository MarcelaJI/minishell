/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:31:44 by iranieri          #+#    #+#             */
/*   Updated: 2025/06/28 18:31:45 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_error(int fd, t_data *data)
{
	if (fd != -1)
		if (close(fd) == -1)
			ms_perror(data);
}

int	dup_close(int oldfd, int newfd, t_data *data)
{
	int	status;

	status = dup2(oldfd, newfd);
	close_error(oldfd, data);
	return (status);
}

void	dupdup(t_data *data, int n)
{
	if (data->in_fds[n])
		if (dup_close(data->in_fds[n], STDIN_FILENO, data) < 0)
			ms_perror(data);
	if (data->out_fds[n])
		if (dup_close(data->out_fds[n], STDOUT_FILENO, data) < 0)
			ms_perror(data);
	if (data->prev_pipe_fd != -1 && !data->in_fds[n])
		if (dup_close(data->prev_pipe_fd, STDIN_FILENO, data) < 0)
			ms_perror(data);
	if (n < data->cmd_count - 1 && !data->out_fds[n])
		if (dup_close(data->pipe_fds[1], STDOUT_FILENO, data) < 0)
			ms_perror(data);
	if (data->prev_pipe_fd != -1 && data->in_fds[n])
		close_error(data->prev_pipe_fd, data);
	if (n < data->cmd_count - 1)
		close_error(data->pipe_fds[0], data);
	if (data->out_fds[n] && n != data->cmd_count - 1)
		close_error(data->pipe_fds[1], data);
}