/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:11:44 by iranieri          #+#    #+#             */
/*   Updated: 2025/07/06 21:56:29 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_list(char **export_arr, int fd)
{
	int	i;

	i = 0;
	if (!export_arr)
		return ;
	while (export_arr[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(export_arr[i++], fd);
	}
}

void	sort_export_list(char **export_arr)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (export_arr[i + 1])
	{
		if (ft_strncmp(export_arr[i], export_arr[i + 1], ft_strlen(export_arr[i])) > 0)
		{
			temp = export_arr[i];
			export_arr[i] = export_arr[i + 1];
			export_arr[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void	ft_export_list(t_data *data)
{
	t_dlist	*temp;
	int		fd;
	char	**export_arr;
	size_t	i;

	temp = data->env;
	if (!temp)
		return ;
	if (data->cmd_count == 1 && data->out_fds[0])
		fd = data->out_fds[0];
	else
		fd = 1;
	export_arr = ft_calloc(listsize(temp) + 1, sizeof(char *));
	check_memory_failure(data, NULL, export_arr, 2);
	i = 0;
	while (temp)
	{
		export_arr[i++] = ms_strdup(temp->str, data);
		temp = temp->next;
	}
	sort_export_list(export_arr);
	i = 0;
	print_export_list(export_arr, fd);
	free_str_array(export_arr, 0);
}

int	ft_export_utils(char *str, t_data *data)
{
	size_t	i;
	int		bad;

	i = 0;
	bad = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		bad = 1;
	while (str[i] && str[i] != '=')
	{
		if (check_invalid_chars_env_var(str[i]))
			bad = 1;
		i++;
	}
	if (bad)
	{
		ft_putstr_fd(SHELLNAME "export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": not a valid identifier", 2);
	}
	else
		add_to_env(str, data);
	return (bad);
}

void	ft_export(t_data *data, int n)
{
	size_t	i;
	int		flag;
	char	**params;

	params = create_exec_array(data, n);
	i = 1;
	flag = 0;
	if (!params[i])
		ft_export_list(data);
	while (params[i])
	{
		if (ft_export_utils(params[i], data))
			flag = 1;
		i++;
	}
	free_str_array(params, 0);
	builtin_exit(data, flag);
}
