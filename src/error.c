/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:25:09 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 11:25:44 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_memory_failure(t_data *data, void *ptr, char **dptr, int f)
{
	if (f == 1)
	{
		if (!ptr)
		{
			ft_putendl_fd(SHELLNAME"Memory allocation failure", 2);
			free_all(data);
			exit(1);
		}
	}
	if (f == 2)
	{
		if (!dptr)
		{
			ft_putendl_fd(SHELLNAME"Memory allocation failure", 2);
			free_all(data);
			exit(1);
		}
	}
}

int	error(char *str, char *token, t_data *data)
{
	(void)data;
	ft_putstr_fd(SHELLNAME, 2);
	if (str && token)
		ft_putstr_fd(str, 2);
	else if (str)
		ft_putendl_fd(str, 2);
	if (token)
		ft_putendl_fd(token, 2);
	return (1);
}

void	ms_perror(t_data *data)
{
	perror(SHELLNAME"error");
	free_all(data);
	exit(1);
}