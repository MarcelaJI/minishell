/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:50:23 by iranieri          #+#    #+#             */
/*   Updated: 2025/06/28 18:23:34 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    builtin_exit(t_data *data, int exit_status)
{
    if (data->cmd_count != 1)
    {
        free_all(data);
        close_error(0, data);
        close_error(1, data);
        exit(exit_status);
    }
    data->exit_status = exit_status;
}

void    exec_single_builtin(t_data *data)
{
    open_here_docs(data, data->tokens, 0);
    open_files(data, data->tokens, 0);
    if (data->open_fail == 1 || g_sig == SIGINT)
        return ;
    exec_builtin(data, 0);
    return ;
}

void    exec_builtin(t_data *data, int n)
{
    if (!ft_strncmp(data->instructions[n], "exit ", 5))
        ft_exit(data, n);
    if (!ft_strncmp(data->instructions[n], "env ", 4))
        ft_env(data);
    if (!ft_strncmp(data->instructions[n], "unset ", 6))
        ft_unset(data, n);
    if (!ft_strncmp(data->instructions[n], "pwd ", 4))
        ft_pwd(data);
    if (!ft_strncmp(data->instructions[n], "echo ", 5))
        ft_echo(data, n);
    if (!ft_strncmp(data->instructions[n], "cd ", 3))
        ft_cd(data, n);
    if (!ft_strncmp(data->instructions[n], "export ", 7))
        ft_export(data, n);
    if (data->cmd_count == 1 && data->in_fds[0])
        close_error(data->in_fds[0], data);
    if (data->cmd_count == 1 && data->out_fds[0])
        close_error(data->out_fds[0], data);
}

int is_builtin(t_data *data, int n)
{
    if (!data->instructions[n])
        return (0);
    if (!ft_strncmp(data->instructions[n], "exit ", 5)
        || !ft_strncmp(data->instructions[n], "env ", 4)
        || !ft_strncmp(data->instructions[n], "export ", 7)
        || !ft_strncmp(data->instructions[n], "echo ", 5)
        || !ft_strncmp(data->instructions[n], "pwd ", 4)
        || !ft_strncmp(data->instructions[n], "cd ", 3)
        || !ft_strncmp(data->instructions[n], "unset ", 6))
        return (1);
    return (0);
}