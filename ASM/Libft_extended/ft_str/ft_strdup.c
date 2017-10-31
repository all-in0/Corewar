/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:32:57 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/15 22:30:38 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	if (!str && !*str)
		return (NULL);
	len = ft_strlen(str);
	tmp = (char*)malloc(sizeof(*str) * (len + 1));
	while (tmp && i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
