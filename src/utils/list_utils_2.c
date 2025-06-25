/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:33:19 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/25 09:27:57 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dlist	*skip_instructions(t_dlist *node, int n)
{
	int	i;

	i = 0;
	while (i < n && node)
	{
		if (node->token == PIPE)
			i++;
		node = node->next;
	}
	return (node);
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

void	refreshindex(t_dlist **list)
{
	t_dlist	*temp;
	int		ind;

	if (!list || !*list)
		return ;
	ind = 0;
	temp = *list;
	while (temp)
	{
		temp->index = ind++;
		temp = temp->next;
	}
}

int	listsize(t_dlist *list)
{
	int		n;
	t_dlist	*temp;

	temp = list;
	n = 0;
	while (temp)
	{
		temp = temp->next;
		n++;
	}
	return (n);
}

t_dlist	*lastnode(t_dlist *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}