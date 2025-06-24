/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:35:22 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 14:37:02 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int validate_token_syntax(t_data *data)
{
    t_dlist *temp;

    temp = data->tokens;

    while (temp)
    {
        if ((is_redirection_token(temp) || temp->token == HERE_DOC) && !temp->next)
            return (error("syntax error near unexpected token: ", "\'newline\'", data));
        if (((temp->index == 0 || temp->index == listsize(data->tokens) - 1) && (temp->token == PIPE)) ||
            (temp->token == PIPE && temp->next && temp->next->token == PIPE) ||
            (is_redirection_token(temp) && is_redirection_token(temp->next)) ||
            (temp->token == HERE_DOC && temp->next && temp->next->token == HERE_DOC) ||
            (temp->token == HERE_DOC && temp->next && temp->next->token != LIMITER) ||
            ((is_redirection_token(temp) || temp->token == HERE_DOC) && temp->next && temp->next->token == PIPE))
            return (error("syntax error near unexpected token: ", temp->str, data));
        if (temp->token == UNKNOWN)
            return (error("unrecognized token: ", temp->str, data));
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

void assign_token_types(t_dlist **tokens)
{
    t_dlist *temp = *tokens;

    while (temp)
    {
        if (!ft_strncmp(temp->str, "|", 2))
            temp->token = PIPE;
        else if (!ft_strncmp(temp->str, ">", 2))
            temp->token = OUTF;
        else if (!ft_strncmp(temp->str, "<", 2))
            temp->token = INF;
        else if (!ft_strncmp(temp->str, "<<", 3))
            temp->token = HERE_DOC;
        else if (!ft_strncmp(temp->str, ">>", 3))
            temp->token = OUTF_APD;
        else if (temp->prev && temp->prev->token == HERE_DOC)
            temp->token = LIMITER;
        else
            assign_token_type_ext(temp);
        temp = temp->next;
    }
}

char *extract_next_word(char *input, size_t *i, t_data *data)
{
    size_t j = 0;
    char q;

    while (input[j] && is_whitespace(input[j]))
    {
        input++;
        (*i)++;
    }
    if (!input[j])
        return (NULL);
    while (input[j] && !is_whitespace(input[j]))
    {
        if (input[j] == '\'' || input[j] == '\"')
        {
            q = input[j++];
            while (input[j] != q)
                j++;
        }
        if (input[j])
            j++;
    }
    return (ms_substr(input, 0, j, data));
}

void tokenize_input_string(char *input, t_data *data)
{
    char *word;
    size_t i = 0;
    t_dlist *temp;

    while (1)
    {
        word = extract_next_word(input + i, &i, data);
        if (!word)
            break;
        temp = newnode(word);
        check_memory_failure(data, temp, NULL, 1);
        node_addback(&data->tokens, temp);
        i += ft_strlen(word);
    }
    assign_token_types(&data->tokens);
}
