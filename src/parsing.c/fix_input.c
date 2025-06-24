/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:09:45 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 13:10:49 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_full_word(char *input, char *str, size_t *a, size_t *b)
{
	char	q;
	size_t	i;
	size_t	j;

	i = *a;
	j = *b;
	while (input[i]
		&& (!is_whitespace(input[i]) || input[i] == '\'' || input[i] == '\"')
		&& !check_redir(input + i))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			q = input[i];
			str[j++] = input[i++];
			while (input[i] && input[i] != q)
				str[j++] = input[i++];
			if (input[i] && input[i] == q)
				str[j++] = input[i++];
		}
		if (input[i])
			str[j++] = input[i++];
	}
	str[j++] = ' ';
	*a = i;
	*b = j;
}

char	*fix_input(char *input, t_data *data)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = ft_calloc((ft_strlen(input) + 1) * 2, sizeof(char));
	check_memory_failure(data, str, NULL, 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (check_redir(input + i))
		{
			str[j++] = input[i++];
			if (check_redir(input + i - 1) == 2)
				str[j++] = input[i++];
			str[j++] = ' ';
		}
		if (input[i] && (!is_whitespace(input[i])
				|| input[i] == '\'' || input[i] == '\"'))
			copy_full_word(input, str, &i, &j);
	}
	free(input);
	return (str);
}