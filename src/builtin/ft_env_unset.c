/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:21:14 by iranieri          #+#    #+#             */
/*   Updated: 2025/06/28 18:21:19 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_data *data, int n)
{
	t_dlist	*temp;
	char	**params;
	int		i;

	params = create_exec_array(data, n);
	i = 1;
	while (params[i])
	{
		temp = get_env_var(ms_strdup(params[i], data), data->env);
		if (temp)
		{
			if (!temp->prev)
				data->env = temp->next;
			if (temp->prev)
				temp->prev->next = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			if (temp->str)
				free(temp->str);
			free(temp);
		}
		i++;
	}
	free_str_array(params, 0);
	builtin_exit(data, 0);
}

void	ft_env(t_data *data)
{
	t_dlist *temp;
	int fd;

	if (data->cmd_count == 1 && data->out_fds[0])
		fd = data->out_fds[0];
	else
		fd = 1;
	temp = data->env;
	while (temp)
	{
		if (ft_strchr(temp->str, '='))
			ft_putendl_fd(temp->str, fd);
		temp = temp->next;
	}
	builtin_exit(data, 0);
}