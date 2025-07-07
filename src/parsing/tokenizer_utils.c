/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:42:33 by ingjimen          #+#    #+#             */
/*   Updated: 2025/07/07 14:33:10 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_token_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || (c == '-') || (c == '.') || (c == '/') || (c == '_')
		|| (c == ',') || (c == ':') || (c == '$') || (c == '\"') || (c == '\'')
		|| (c == '+'))
		return (1);
	return (0);
}

int	is_redirection_token(t_dlist *node)
{
	if (!node)
		return (0);
	if (node->token == INF || node->token == OUTF || node->token == OUTF_APD)
		return (1);
	return (0);
}

int	has_command_before_pipe(t_dlist *node)
{
	node = node->prev;
	if (node->token == PIPE)
		return (0);
	while (node && node->token != PIPE)
	{
		if (node->token == CMD)
			return (1);
		node = node->prev;
	}
	return (0);
}
