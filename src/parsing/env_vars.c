/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:48:28 by ingjimen          #+#    #+#             */
/*   Updated: 2025/07/02 11:15:01 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_env_var(char *env_str, size_t *j, char *exp)
{
	size_t	temp;

	temp = *j;
	ft_strlcpy(exp + temp, env_str, ft_strlen(env_str) + 1);
	temp += ft_strlen(env_str);
	free(env_str);
	*j = temp;
}

void	expand_env_vars_loop(char *str, char *exp, char *env_str, t_data *data)
{
	size_t	i;
	size_t	j;
	int		dquote;
	int		squote;

	i = 0;
	j = 0;
	dquote = 0;
	squote = 0;
	while (str[i])
	{
		update_double_quote_flag(str, &dquote, &squote, &i);
		update_single_quote_flag(str, &squote, &dquote, &i);
		if (str[i] == '$' && (!check_invalid_chars_env_var(str[i + 1]) || str[i
				+ 1] == '?' || str[i + 1] == '$') && !squote)
		{
			env_str = get_env_var_str(str + i + 1, data);
			if (env_str)
				copy_env_var(env_str, &j, exp);
			i += env_var_name_len(str + i + 1) + 1;
		}
		else if (str[i])
			exp[j++] = str[i++];
	}
}

char	*expand_env_vars(char *str, t_data *data)
{
	char	*exp;
	char	*env_str;

	if (!ft_strchr(str, '$'))
		return (str);
	env_str = NULL;
	if (get_exp_len(str, data) == 0)
	{
		free(str);
		return (NULL);
	}
	exp = ft_calloc(get_exp_len(str, data) + 1, sizeof(char));
	check_memory_failure(data, exp, NULL, 1);
	expand_env_vars_loop(str, exp, env_str, data);
	free(str);
	return (exp);
}

char	**convert_env_to_strings(t_data *data)
{
	int i;
	t_dlist *temp;
	char **env;

	i = 0;
	temp = data->env;
	env = NULL;
	while (temp)
	{
		if (ft_strchr(temp->str, '='))
			i++;
		temp = temp->next;
	}
	env = ft_calloc(i + 1, sizeof(char *));
	check_memory_failure(data, NULL, env, 2);
	i = 0;
	temp = data->env;
	while (temp)
	{
		if (ft_strchr(temp->str, '='))
			env[i++] = ms_strdup(temp->str, data);
		temp = temp->next;
	}
	return (env);
}