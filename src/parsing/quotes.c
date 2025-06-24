/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:09:31 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 12:14:20 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_double_quote_flag(char *str, int *dquote, int *squote, size_t *i)
{
	size_t	j;

	j = *i;
	if (str[j] == '\"' && *dquote == 1)
		*dquote = 0;
	else if (str[j] == '\"' && *dquote == 0 && squote && *squote == 0)
		*dquote = 1;
	else if (str[j] == '\"' && *dquote == 0 && !squote)
		*dquote = 1;
}

void	update_single_quote_flag(char *str, int *squote, int *dquote, size_t *i)
{
	size_t	j;

	j = *i;
	if (str[j] == '\'' && *squote == 1)
		*squote = 0;
	else if (str[j] == '\'' && *squote == 0 && *dquote == 0)
		*squote = 1;
}

void	skip_quoted_single_block(char *str, int *dquote, int *squote, size_t *i)
{
	size_t	j;

	j = *i;
	update_double_quote_flag(str, dquote, squote, i);
	if (str[j] == '\'' && *dquote == 0)
	{
		j++;
		while (str[j] && str[j] != '\'')
			j++;
		if (str[j] && str[j] == '\'')
			j++;
	}
	*i = j;
}

char	*strip_quotes_from_string(char *str, t_data *data)
{
	size_t	i;
	size_t	j;
	char	q;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	check_memory_failure(data, new, NULL, 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i++];
			while (str[i] && str[i] != q)
				new[j++] = str[i++];
			if (str[i] == q)
				i++;
		}
		else
			new[j++] = str[i++];
	}
	free(str);
	return (new);
}

void	strip_all_token_quotes(t_data *data)
{
	t_dlist	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->str)
			temp->str = strip_quotes_from_string(temp->str, data);
		temp = temp->next;
	}
}

