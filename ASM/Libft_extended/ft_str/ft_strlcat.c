/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:33:27 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:58:58 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;

	i = ft_strlen(dst);
	if (i >= size)
		return (size + ft_strlen(src));
	else
	{
		while (i < size - 1 && *src)
			dst[i++] = *src++;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
