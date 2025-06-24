/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:32:32 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 12:45:00 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int validate_token_syntax(char *input)
{
	char	q;
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			q = input[i++];
			while (input[i] && input[i] != q)
				i++;
			if (!input[i])
				return (1);
		}
		i++;
	}
	return (0);
}