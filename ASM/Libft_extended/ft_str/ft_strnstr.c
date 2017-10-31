/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:35:05 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:58:51 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	if (find[0] == '\0')
		return ((char*)str);
	while (str[i] && n > 0)
	{
		j = 0;
		k = n;
		while (find[j] && str[i + j] == find[j] && n > 0)
		{
			j++;
			n--;
		}
		if (find[j] == '\0')
			return ((char*)str + i);
		n = k;
		i++;
		n--;
	}
	return (0);
}
