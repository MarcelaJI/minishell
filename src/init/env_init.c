/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:54:20 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/26 11:59:10 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_env(char *str, t_data *data)
{
	t_dlist	*temp;

	temp = data->env;
	while (temp)
	{
		if (!cmp_up_to_equal(str, temp->str))
		{
			if (ft_strchr(str, '='))
			{
				free(temp->str);
				temp->str = ms_strdup(str, data);
				return ;
			}
			else
				return ;
		}
		temp = temp->next;
	}
	temp = newnode(ms_strdup(str, data));
	check_memory_failure(data, temp, NULL, 1);
	node_addback(&data->env, temp);
}

void	update_oldpwd(t_dlist *env, t_data *data)
{
	t_dlist	*temp;
	char	*oldpwd;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp("OLDPWD=", temp->str, 7))
		{
			oldpwd = temp->str;
			temp->str = ms_strjoin("OLDPWD=", get_env_var_str("PWD", data), 2,
					data);
			free(oldpwd);
			return ;
		}
		temp = temp->next;
	}
	node_addback(&env, newnode(ms_strjoin("OLDPWD=", get_env_var_str("PWD",
					data), 2, data)));
}

void	update_pwd(t_dlist *env, t_data *data)
{
	t_dlist	*temp;
	char	*cwd;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp("PWD=", temp->str, 4))
		{
			cwd = getcwd(NULL, 0);
			free(temp->str);
			temp->str = ms_strjoin("PWD=", cwd, 2, data);
			return ;
		}
		temp = temp->next;
	}
	cwd = getcwd(NULL, 0);
	node_addback(&env, newnode(ms_strjoin("PWD=", cwd, 2, data)));
}

void	update_shlvl(t_dlist *env, t_data *data)
{
	t_dlist	*temp;
	int		shlvl;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp("SHLVL=", temp->str, 6))
		{
			shlvl = ft_atoi(temp->str + 6) + 1;
			free(temp->str);
			temp->str = ms_strdup("SHLVL=", data);
			temp->str = ms_strjoin(temp->str, ft_itoa(shlvl), 3, data);
			return ;
		}
		temp = temp->next;
	}
	node_addback(&data->env, newnode(ms_strdup("SHLVL=1", data)));
}

void	create_env(t_data *data, char **env)
{
	int i;
	t_dlist *temp;

	i = 0;
	if (env && env[i])
	{
		while (env[i])
		{
			temp = newnode(ms_strdup(env[i++], data));
			check_memory_failure(data, temp, NULL, 1);
			node_addback(&data->env, temp);
		}
	}
	update_shlvl(data->env, data);
	update_pwd(data->env, data);
}