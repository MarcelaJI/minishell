/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:30:06 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/25 09:28:02 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	node_addback(t_dlist **list, t_dlist *new)
{
	t_dlist	*temp;

	if (!list || !*list)
	{
		*list = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		temp = lastnode(*list);
		new->prev = temp;
		temp->next = new;
	}
	refreshindex(list);
}

void	node_addfront(t_dlist **list, t_dlist *node)
{
	if (!*list)
	{
		*list = node;
		node->next = NULL;
		node->prev = NULL;
	}
	else
	{
		(*list)->prev = node;
		node->next = *list;
		node->prev = NULL;
		*list = node;
	}
	refreshindex(list);
}

t_dlist	*newnode(char *str)
{
	t_dlist *node;

	node = ft_calloc(sizeof(t_dlist), 1);
	if (!node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->str = str;
	node->token = -1;
	node->index = 0;
	return (node);
}