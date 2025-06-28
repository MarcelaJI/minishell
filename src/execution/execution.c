/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 9:25:22 by iranieri          #+#    #+#             */
/*   Updated: 2025/06/28 18:25:25 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execve_fail(char *cmd, char **execve_arr, char **env, t_data *data)
{
    ft_putstr_fd(SHELLNAME, 2);
    ft_putstr_fd(cmd, 2);
    if (errno == EACCES)
    {
        ft_putendl_fd(": Permission denied", 2);
        free(cmd);
        free_str_array(env, 0);
        free_str_array(execve_arr, 0);
        free_all(data);
        close_error(0, data);
        close_error(1, data);
        exit(126);
    }
    else
    {
        ft_putendl_fd(": Command not found", 2);
        free(cmd);
        free_str_array(env, 0);
        free_str_array(execve_arr, 0);
        free_all(data);
        close_error(0, data);
        close_error(1, data);
        exit(127); 
    }
}


void    exec_single_cmd(t_data *data, int n)
{
    char    **execve_arr;
    char    **env;
    char    *cmd;

    if (!data->instructions[n])
        return ;
    if (is_builtin(data, n))
        exec_builtin(data, n);
    else
    {
        execve_arr = create_exec_array(data, n);
        env = convert_env_to_strings(data);
        cmd = ms_strdup(execve_arr[0], data);
        execve_arr[0] = search_path(execve_arr[0], env, data);
        execve(execve_arr[0], execve_arr, env);
        execve_fail(cmd, execve_arr, env, data);
    }
    exit(127 - (errno == EACCES));
}

void    execution_child(t_data *data, int i)
{
    signal(SIGQUIT, SIG_DFL);
    open_files(data, data->tokens, i);
    dupdup(data, i);
    exec_single_cmd(data, i);
}

void    execution_parent(t_data *data, int i)
{
    signal(SIGINT, do_nothing);
    data->pids[i] = fork();
    if (data->pids[i] == 0)
        execution_child(data, i);
    else if (data->pids[i] < 0)
        ms_perror(data);
    if (data->in_fds[i])
        close_error(data->in_fds[i], data);
    if (i < data->cmd_count - 1)
        close_error(data->pipe_fds[1], data);
    if (data->prev_pipe_fd != -1)
        close_error(data->prev_pipe_fd, data);
    if (data->cmd_count > 1)
        data->prev_pipe_fd = data->pipe_fds[0];
}

void    execution(t_data *data)
{
    int i;

    i = 0;
    while (i < data->cmd_count && exit_nbr != SIGINT)
    {
        open_heredoc(data, data->tokens, i);
        if (exit_nbr == SIGINT)
        {
            if (data->in_fds[i])
                close_error(data->in_fds[i], data);
            break ;
        }
        if (i < data->cmd_count - 1)
            if (pipe(data->pipe_fds) < 0)
                ms_perror(data);
        execution_parent(data, i);
        i++;
    }
    if (exit_nbr == SIGINT)
        data->exit_status = 130;
    else
        exit_status(data->pids[i - 1], data);
    exit_nbr = -1;
}

