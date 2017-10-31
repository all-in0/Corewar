/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:37:35 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:58:57 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*tmp;
	int		i;

	i = 0;
	if (s)
	{
		if ((tmp = ft_strnew(ft_strlen(s))))
		{
			while (*s)
				tmp[i++] = f(*s++);
		}
		return (tmp);
	}
	return (0);
}
