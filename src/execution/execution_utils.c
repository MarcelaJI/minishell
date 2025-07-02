/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:24:26 by iranieri          #+#    #+#             */
/*   Updated: 2025/07/02 09:30:11 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    set_cmd_count(t_data *data)
{
    t_dlist *temp;

    data->cmd_count = 1;
    temp = data->tokens;
    while (temp)
    {
        if (temp->token == PIPE)
            data->cmd_count++;
        temp = temp->next;
    }
}

char    **create_exec_array(t_data *data, int n)
{
    t_dlist *temp;
    size_t  i;
    char    **exec_arr;

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

void    convert_tokens(t_data *data)
{
    t_dlist *temp;
    int     i;

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
                data->instructions[i] = ms_strjoin
                    (data->instructions[i], temp->str, 1, data);
            if ((temp->token == CMD || temp->token == PARAM) && temp->str)
                data->instructions[i] = ms_strjoin
                    (data->instructions[i], " ", 1, data);
            temp = temp->next;
        }
        i++;
    }
}

void exit_status(pid_t pid, t_data *data)
{
    pid_t   temp;
    int     status;
    int     last_status;
    int     sig_exit;

    last_status = 0;
    sig_exit = 0;
    while (1)
    {
        temp = wait(&status);
        if (temp <= 0)
            break ;
        if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            if (sig == SIGQUIT)
                ft_putendl_fd("Quit", 2);
            else if (sig == SIGINT)
                ft_putchar_fd('\n', 2);

            sig_exit = 128 + sig;
        }
        if (temp == pid)
        {
            if (WIFEXITED(status))
                last_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                last_status = 128 + WTERMSIG(status);
        }
    }
    if (sig_exit)
        data->exit_status = sig_exit;
    else
        data->exit_status = last_status;
}


void    alloc_fd_pid_arrays(t_data *data)
{
    data->in_fds = ft_calloc(data->cmd_count, sizeof(int));
    check_memory_failure(data, data->in_fds, NULL, 1);
    data->out_fds = ft_calloc(data->cmd_count, sizeof(int));
    check_memory_failure(data, data->out_fds, NULL, 1);
    data->pids = ft_calloc(data->cmd_count, sizeof(pid_t));
    check_memory_failure(data, data->pids, NULL, 1);
}