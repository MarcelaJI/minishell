/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:32:32 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 13:19:06 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *input)
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

void	expand_all_tokens(t_data *data)
{
	t_dlist	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->token != LIMITER)
			temp->str = expand_env_vars(temp->str, data); // Esperando parte del código de Imma
		temp = temp->next;
	}
}

int	check_empty_input(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (!input[i] || !ft_strncmp(input, "", 1))
		return (1);
	return (0);
}

/*
int	parse_input(t_data *data)
{
	if (check_empty_input(data->input))
		return (1);
	add_history(data->input);
	if (check_quotes(data->input))
	{
		data->exit_status = 258;
		return (error("syntax error: unclosed quotations", NULL, data));
	}
	data->input = fix_input(data->input, data);
	tokenize_input_string(data->input, data);
	if (validate_token_syntax(data))
	{
		data->exit_status = 258;
		return (1);
	}
	expand_all_tokens(data);
	strip_all_token_quotes(data);
	convert_tokens(data); -> parte de la ejecución esperando a Imma
	return (0);
}

*/