/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:20:52 by iranieri          #+#    #+#             */
/*   Updated: 2025/07/02 09:50:42 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_echo_newline(char **params, int *newline)
{
	size_t	i;
	size_t	j;

	i = 1;
	*newline = 1;
	while (params[i])
	{
		j = 0;
		if (params[i][j] == '-' && params[i][j + 1])
		{
			j++;
			while (params[i][j] && params[i][j] == 'n')
				j++;
			if (!params[i][j])
				*newline = 0;
			else
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(t_data *data, int n)
{
	char	**params;
	size_t	i;
	int		fd;
	int		newline;

	params = create_exec_array(data, n);
	if (data->cmd_count == 1 && data->out_fds[0])
		fd = data->out_fds[0];
	else
		fd = 1;
	i = ft_echo_newline(params, &newline);
	while (params[i])
	{
		ft_putstr_fd(params[i], fd);
		if (params[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", fd);
	free_str_array(params, 0);
	builtin_exit(data, 0);
}
