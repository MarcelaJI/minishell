/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:34:38 by iranieri          #+#    #+#             */
/*   Updated: 2025/07/06 21:09:20 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_error_msg(char **params, char *msg, t_data *data)
{
	ft_putendl_fd(SHELLNAME "cd: ", 2);
	ft_putendl_fd(msg, 2);
	free_str_array(params, 0);
	ft_exit(data, 1);
	return (NULL);
}

static char	*cd_get_target_dir(char **params, t_data *data)
{
	char	*home;
	char	*oldpwd;

	if (!params[1])
	{
		home = get_env_var_str("HOME", data);
		if (!home)
			return (cd_error_msg(params, "HOME not set", data));
		return (home);
	}
	else if (!ft_strncmp(params[1], "-", 2))
	{
		oldpwd = get_env_var_str("OLDPWD", data);
		if (!oldpwd)
			return (cd_error_msg(params, "OLDPWD not set", data));
		return (oldpwd);
	}
	return (ms_strdup(params[1], data));
}

static void	cd_handle_chdir(char **params, char *dir, t_data *data)
{
	int	fail;

	fail = 0;
	if (chdir(dir) == -1)
	{
		ft_putstr_fd(SHELLNAME "cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		fail = 1;
	}
	if (!fail && params[1] && !ft_strncmp(params[1], "-", 2))
		ft_putendl_fd(dir, 1);
	if (!fail)
	{
		update_oldpwd(data->env, data);
		update_pwd(data->env, data);
	}
	free_str_array(params, 0);
	if (dir)
		free(dir);
	builtin_exit(data, fail);
}

void	ft_cd(t_data *data, int n)
{
	char	**params;
	char	*dir;

	params = create_exec_array(data, n);
	dir = cd_get_target_dir(params, data);
	if (!dir)
		return ;
	cd_handle_chdir(params, dir, data);
}

void	ft_pwd(t_data *data)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	check_memory_failure(data, cwd, NULL, 1);
	if (data->cmd_count == 1 && data->out_fds[0])
		ft_putendl_fd(cwd, data->out_fds[0]);
	else
		ft_putendl_fd(cwd, 1);
	free(cwd);
	builtin_exit(data, 0);
}