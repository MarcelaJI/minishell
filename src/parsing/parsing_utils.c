/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:05:51 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 13:07:55 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || (c == '-') || (c == '.') || (c == '/') || (c == '_')
		|| (c == ',') || (c == ':') || (c == '$') || (c == '^') || (c == '+'))
		return (1);
	return (0);
}

int	check_redir(char *c)
{
	int	ch;

	if (c[0] == '|')
		return (1);
	if (c[0] == '>' || c[0] == '<')
	{
		ch = c[0];
		if (c[1] == ch)
			return (2);
		else
			return (1);
	}
	return (0);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	checkfornum(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[i])
	{
		n = ft_isdigit(s[i]);
		if (!n)
			return (n);
		i++;
	}
	return (n);
}

int	cmp_up_to_equal(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if ((s1[i] == '=' && !s2[i]) || (!s1[i] && s2[i] == '='))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}