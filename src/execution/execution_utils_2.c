/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:22:11 by ingjimen          #+#    #+#             */
/*   Updated: 2025/07/07 14:21:29 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0)
		return (S_ISDIR(statbuf.st_mode));
	return (0);
}

void	exec_external_cmd(t_data *data, int n)
{
	char	**execve_arr;
	char	**env;
	char	*cmd;

	execve_arr = create_exec_array(data, n);
	if (execve_arr[0] && ft_strcmp(execve_arr[0], ".") == 0 && !execve_arr[1])
	{
		ft_putendl_fd(SHELLNAME ".: filename argument required", 2);
		free_str_array(execve_arr, 0);
		free_all(data);
		exit(2);
	}
	if (execve_arr[0] && ft_strcmp(execve_arr[0], "..") == 0)
	{
		ft_putendl_fd(SHELLNAME "..: command not found", 2);
		free_str_array(execve_arr, 0);
		free_all(data);
		exit(127);
	}
	env = convert_env_to_strings(data);
	cmd = ms_strdup(execve_arr[0], data);
	execve_arr[0] = search_path(execve_arr[0], env, data);
	execve(execve_arr[0], execve_arr, env);
	execve_fail(cmd, execve_arr, env, data);
}

void	alloc_fd_pid_arrays(t_data *data)
{
	data->in_fds = ft_calloc(data->cmd_count, sizeof(int));
	check_memory_failure(data, data->in_fds, NULL, 1);
	data->out_fds = ft_calloc(data->cmd_count, sizeof(int));
	check_memory_failure(data, data->out_fds, NULL, 1);
	data->pids = ft_calloc(data->cmd_count, sizeof(pid_t));
	check_memory_failure(data, data->pids, NULL, 1);
}
