/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:34:38 by iranieri          #+#    #+#             */
/*   Updated: 2025/06/29 09:05:44 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void    ft_cd_utils(char **params, char *dir, t_data *data)
{
    int fail;

    fail = 0;
    if (chdir(dir) == -1)
    {
        ft_putstr_fd(SHELLNAME"cd: ", 2);
        ft_putstr_fd(dir, 2);
        ft_putstr_fd(": ", 2);
        perror(NULL);
        fail = 1;
    }
    if (!fail && params[1] && !ft_strncmp(params[1], "-", 2))
        ft_putendl_fd(dir, 1); // imprimir ruta si es "cd -"
    if (dir)
        free(dir);
    if (!fail)
    {
        update_oldpwd(data->env, data);
        update_pwd(data->env, data);
    }
    free_str_array(params, 0);
    builtin_exit(data, fail);
}

void    ft_cd(t_data *data, int n)
{
    char    **params;
    char    *dir;

    params = create_exec_array(data, n);
    dir = NULL;
    if (!params[1]) // cd
    {
        dir = get_env_var_str("HOME", data);
        if (!dir)
        {
            ft_putendl_fd(SHELLNAME"cd: HOME not set", 2);
            free_str_array(params, 0);
            ft_exit(data, 1);
            return ;
        }
    }
    else if (!ft_strncmp(params[1], "-", 2)) // cd -
    {
        dir = get_env_var_str("OLDPWD", data);
        if (!dir)
        {
            ft_putendl_fd(SHELLNAME"cd: OLDPWD not set", 2);
            free_str_array(params, 0);
            ft_exit(data, 1);
            return ;
        }
    }
    else // cd <path>
        dir = ms_strdup(params[1], data);
    ft_cd_utils(params, dir, data);
}



void    ft_pwd(t_data *data)
{
    char    *cwd;

    cwd = getcwd(NULL, 0);
    check_memory_failure(data, cwd, NULL, 1);
    if (data->cmd_count == 1 && data->out_fds[0])
        ft_putendl_fd(cwd, data->out_fds[0]);
    else
        ft_putendl_fd(cwd, 1);
    free(cwd);
    builtin_exit(data, 0);
}