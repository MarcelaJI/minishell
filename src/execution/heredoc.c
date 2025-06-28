/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:30:12 by iranieri          #+#    #+#             */
/*   Updated: 2025/06/28 18:39:52 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    exit_heredoc(t_data *data, char *limiter, char *line)
{
    if (!line || (!ft_strncmp(line, limiter, ft_strlen(limiter))
            && ft_strlen(line) == ft_strlen(limiter)))
    {
        close_error(data->pipe_fds[1], data);
        free(line);
        free_all(data);
        exit(0);
    }
}

void    heredoc_child(t_data *data, t_dlist *node)
{
    char    *line;

    signal(SIGINT, hdc_sig);
    signal(SIGQUIT, SIG_IGN);
    if (data->prev_pipe_fd != -1)
        close_error(data->prev_pipe_fd, data);
    close_error(data->pipe_fds[0], data);
    while (1)
    {
        line = readline("> ");
        if (exit_nbr == SIGINT)
        {
            if (line)
                free(line);
            close_error(data->pipe_fds[1], data);
            free_all(data);
            exit(1);
        }
        exit_heredoc(data, node->str, line);
        line = expand_env_vars(line, data);
        line = ms_strjoin(line, "\n", 1, data);
        ft_putstr_fd(line, data->pipe_fds[1]);
        free(line);
    }
}

int heredoc(t_data *data, t_dlist *node)
{
    pid_t   pid;

    if (pipe(data->pipe_fds) == -1)
        ms_perror(data);
    signal(SIGINT, do_nothing);
    signal(SIGQUIT, SIG_IGN);
    pid = fork();
    if (pid == -1)
        ms_perror(data);
    if (!pid)
        heredoc_child(data, node);
    close_error(data->pipe_fds[1], data);
    waitpid(pid, NULL, 0);
    return (data->pipe_fds[0]);
}

int heredoc_check(t_dlist *node, int n)
{
    int hdc;

    hdc = 0;
    node = skip_instructions(node, n);
    while (node && node->token != PIPE)
    {
        if (node->token == HERE_DOC)
            hdc = 1;
        else if (node->token == INF)
            hdc = 0;
        node = node->next;
    }
    return (hdc);
}

void    open_heredoc(t_data *data, t_dlist *node, int n)
{
    int in_fd;

    in_fd = 0;
    node = skip_instructions(node, n);
    while (node && node->token != PIPE)
    {
        if (node->token == HERE_DOC && exit_nbr != SIGINT)
        {
            if (in_fd)
                close_error(in_fd, data);
            in_fd = heredoc(data, node->next);
        }
        node = node->next;
    }
    if (exit_nbr == SIGINT && in_fd)
        close_error(in_fd, data);
    else
        data->in_fds[n] = in_fd;
}