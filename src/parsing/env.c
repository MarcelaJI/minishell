/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:47:56 by ingjimen          #+#    #+#             */
/*   Updated: 2025/07/06 12:41:30 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var_str(char *str, t_data *data)
{
	size_t	i;
	t_dlist	*temp;
	char	*itoa;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '?' || str[0] == '$')
		i++;
	else
		while (!check_invalid_chars_env_var(str[i]))
			i++;
	if (i)
	{
		if (str[0] == '?')
		{
			itoa = ft_itoa(data->exit_status);
			check_memory_failure(data, itoa, NULL, 1);
			return (itoa);
		}
		temp = get_env_var(ms_substr(str, 0, i, data), data->env);
		if (temp)
			return (ms_strdup(temp->str + i + 1, data));
	}
	return (NULL);
}

t_dlist	*get_env_var(char *var, t_dlist *env)
{
	t_dlist	*temp;

	temp = env;
	while (temp)
	{
		if (!cmp_up_to_equal(var, temp->str))
		{
			free(var);
			return (temp);
		}
		temp = temp->next;
	}
	free(var);
	return (NULL);
}

char	*find_path_in_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

char	*search_path(char *cmd, char **env, t_data *data)
{
	char	*path_env;

	if (!cmd || !cmd[0])
		return (cmd);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	path_env = find_path_in_env(env);
	if (!path_env)
		return (NULL);
	return (search_in_path(cmd, path_env, data));
}

char	*search_in_path(char *cmd, char *path_env, t_data *data)
{
	char	**env_words;
	char	*path;
	int		i;

	env_words = ft_split(path_env, ':');
	if (!env_words)
		return (NULL);
	i = -1;
	while (env_words[++i])
	{
		path = ms_strjoin(env_words[i], "/", 0, data);
		path = ms_strjoin(path, cmd, 1, data);
		if (!access(path, X_OK | F_OK))
		{
			free_str_array(env_words, 0);
			free(cmd);
			return (path);
		}
		free(path);
	}
	free_str_array(env_words, 0);
	return (NULL);
}
