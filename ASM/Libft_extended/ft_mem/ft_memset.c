/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:42:56 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:59:13 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char *tmp;

	tmp = (unsigned char*)str;
	while (n-- > 0)
		*tmp++ = (unsigned char)c;
	return (str);
}
