/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:02:45 by ingjimen          #+#    #+#             */
/*   Updated: 2024/09/30 08:49:28 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t  i;
    int    j;
    unsigned char *s;
    unsigned char *d;

    i = 0;
    j = 1;
    s = (unsigned char *)src;
    d = (unsigned char *)dest;
    if ((!dest || !src) && n > 0)
        return (NULL);
    if (dest > src)
    {
        j = -1;
        d += n - 1;
        s += n - 1;
    }
    while (i < n)
    {
        *d = *s;
        d += j;
        s += j;
        i++;
    }
    return (dest);
}
