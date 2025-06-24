/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:17:55 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 12:13:45 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_substr(char const *s, unsigned int start, size_t len, t_data *data)
{
	char	*sub;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start > slen || !len)
		return (ft_strdup(""));
	if (start + len > slen)
		sub = ft_calloc(sizeof(char), (slen - start + 1));
	else
		sub = ft_calloc(sizeof(char), (len + 1));
	check_memory_failure(data, sub, NULL, 1);
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

void	free_all(t_data *data)
{
    if (data->tokens)
		freelist(data->tokens);
}


void	freelist(t_dlist *list)
{
	t_dlist	*temp;

	while (list)
	{
		if (list->str)
			free(list->str);
		temp = list;
		list = list->next;
		free(temp);
	}
}