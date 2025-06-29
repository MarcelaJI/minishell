/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:39:10 by ingjimen          #+#    #+#             */
/*   Updated: 2024/09/29 20:29:19 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dest, const char *src, size_t dsize)
{
	size_t	i;
	size_t	j;
	size_t	r;

	i = 0;
	while (dest[i] != '\0')
		++i;
	r = 0;
	while (src[r] != '\0')
		++r;
	if (dsize <= i)
		r += dsize;
	else
		r += i;
	j = 0;
	while (src[j] != '\0' && i + 1 < dsize)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (r);
}
