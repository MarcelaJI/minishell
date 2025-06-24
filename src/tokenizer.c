/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:35:22 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 11:00:38 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int validate_token_syntax(t_data *data)
{
    t_dlist *temp = data->tokens;

    while (temp)
    {
        if ((is_redirection_token(temp) || temp->token == HERE_DOC) && !temp->next)
            return error("syntax error near unexpected token: ", "\'newline\'", data);
        if (((temp->index == 0 || temp->index == listSize(data->tokens) - 1) && (temp->token == PIPE)) ||
            (temp->token == PIPE && temp->next && temp->next->token == PIPE) ||
            (is_redirection_token(temp) && is_redirection_token(temp->next)) ||
            (temp->token == HERE_DOC && temp->next && temp->next->token == HERE_DOC) ||
            (temp->token == HERE_DOC && temp->next && temp->next->token != LIMITER) ||
            ((is_redirection_token(temp) || temp->token == HERE_DOC) && temp->next && temp->next->token == PIPE))
            return error("syntax error near unexpected token: ", temp->str, data);
        if (temp->token == UNKNOWN)
            return error("unrecognized token: ", temp->str, data);
        temp = temp->next;
    }
    return 0;
}