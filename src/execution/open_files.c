/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:28:25 by iranieri          #+#    #+#             */
/*   Updated: 2025/06/28 18:31:38 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    open_error(t_data *data, int in_fd, int out_fd, int n)
{
    if (in_fd > 0)
        close_error(in_fd, data);
    if (out_fd > 0)
        close_error(out_fd, data);
    if (data->in_fds[n] > 0)
        close_error(data->in_fds[n], data);
    if (!(data->cmd_count == 1 && is_builtin(data, 0)))
    {
        if (n != data->cmd_count - 1)
        {
            close_error(data->pipe_fds[0], data);
            close_error(data->pipe_fds[1], data);
            if (n > 0)
                close_error(data->prev_pipe_fd, data);
        }
        if (n == data->cmd_count - 1 && data->cmd_count > 1)
            close_error(data->prev_pipe_fd, data);
        free_all(data);
        exit(1);
    }
    data->exit_status = 1;
    data->open_fail = 1;
}

int open_outfile(t_data *data, t_dlist *node, int out_fd, int apd)
{
    if (out_fd)
        close_error(out_fd, data);
    if (apd)
        out_fd = open(node->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        out_fd = open(node->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    return (out_fd);
}

int open_infile(t_data *data, t_dlist *node, int in_fd)
{
    if (in_fd)
        close_error(in_fd, data);
    in_fd = open(node->str, O_RDONLY);
    return (in_fd);
}

void    open_files_extension(t_data *data, int in_fd, int out_fd, int n)
{
    if (heredoc_check(data->tokens, n) && in_fd > 0)
        close_error(in_fd, data);
    else if (!heredoc_check(data->tokens, n))
    {
        if (data->in_fds[n])
            close_error(data->in_fds[n], data);
        data->in_fds[n] = in_fd;
    }
    data->out_fds[n] = out_fd;
    if (!data->instructions[n])
    {
        if (data->out_fds[n])
            close_error(data->out_fds[n], data);
        if (data->in_fds[n])
            close_error(data->in_fds[n], data);
        if (data->prev_pipe_fd != -1)
            close_error(data->prev_pipe_fd, data);
        if (n < data->cmd_count - 1)
        {
            close_error(data->pipe_fds[1], data);
            close_error(data->pipe_fds[0], data);
        }
        free_all(data);
        exit(0);
    }
}