/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:22:11 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/29 09:23:09 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_directory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) == 0)
        return S_ISDIR(statbuf.st_mode);
    return 0;
}