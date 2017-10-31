/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 20:45:56 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:58:44 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int		ft_length(long int n)
{
	int i;

	i = 0;
	if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	char	*ft_make(char *str, int len, long l, int n)
{
	str[len] = '\0';
	while (l > 9)
	{
		str[--len] = (l % 10) + '0';
		l = l / 10;
	}
	str[--len] = l + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}

char			*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	l;

	l = (long int)n;
	len = ft_length(l);
	if (l < 0)
	{
		len = len + 1;
		l = -l;
	}
	if ((str = (char*)malloc(sizeof(char) * len + 1)))
		return (ft_make(str, len, l, n));
	return (NULL);
}
