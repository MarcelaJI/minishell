/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:35:22 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 11:11:02 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int validate_token_syntax(t_data *data)
{
    t_dlist *temp;

    temp = data->tokens;

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
    return (0);
}

void assign_token_type_ext(t_dlist *temp)
{
    if ((temp->index == 0) ||
        (temp->prev && temp->prev->token == PIPE) ||
        (temp->prev && !has_command_before_pipe(temp) && (temp->prev->token == FILENAME || temp->prev->token == LIMITER)))
        temp->token = CMD;
    else if (temp->prev && has_command_before_pipe(temp) && !is_redirection_token(temp->prev) &&
            (temp->prev->token == FILENAME || temp->prev->token == CMD || temp->prev->token == LIMITER || temp->prev->token == PARAM))
        temp->token = PARAM;
    else if (temp->prev && is_redirection_token(temp->prev))
        temp->token = FILENAME;
    else
        temp->token = UNKNOWN;
}