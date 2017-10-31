/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 20:56:58 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:58:46 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#define TAB(x) (x == ' ' || x == '\t' || x == '\n')

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (TAB(s[i]))
			i++;
		while (TAB(s[len - 1]))
			len--;
		len = len - i;
		if (len < 0)
			len = 0;
		str = ft_strsub(s, i, len);
		return (str);
	}
	return (NULL);
}
