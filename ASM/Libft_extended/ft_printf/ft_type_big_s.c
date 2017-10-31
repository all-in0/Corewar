/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_big_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 21:14:11 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/02/27 15:16:05 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_length_wchar(wchar_t wchar)
{
	if (wchar <= 0x7F)
		return (1);
	else if (wchar <= 0x7FF)
		return (2);
	else if (wchar <= 0xFFFF)
		return (3);
	else
		return (4);
	return (0);
}

static int		ft_length_str(wchar_t *wchar)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (wchar[++i])
		len += ft_length_wchar(wchar[i]);
	return (len);
}

static	void	ft_wchar_to_char(t_lst *list, wchar_t wchar, char *str, int *i)
{
	int		len;

	len = ft_length_wchar(wchar);
	if (len == 1 && (len + *i <= list->precision || list->precision == 0))
		str[(*i)++] = wchar;
	else if (len == 2 && (len + *i <= list->precision || list->precision == 0))
	{
		str[(*i)++] = (wchar >> 6) + 0xC0;
		str[(*i)++] = (wchar & 0x3F) + 0x80;
	}
	else if (len == 3 && (len + *i <= list->precision || list->precision == 0))
	{
		str[(*i)++] = (wchar >> 12) + 0xE0;
		str[(*i)++] = ((wchar >> 6) & 0x3F) + 0x80;
		str[(*i)++] = (wchar & 0x3F) + 0x80;
	}
	else if (len + *i <= list->precision || list->precision == 0)
	{
		str[(*i)++] = (wchar >> 18) + 0xF0;
		str[(*i)++] = ((wchar >> 12) & 0x3F) + 0x80;
		str[(*i)++] = ((wchar >> 6) & 0x3F) + 0x80;
		str[(*i)++] = (wchar & 0x3F) + 0x80;
	}
}

int				ft_type_big_s(t_lst *list, va_list ap)
{
	wchar_t		*wchar;
	int			len;
	int			i;
	int			j;

	i = -1;
	j = 0;
	if (!(wchar = va_arg(ap, wchar_t*)))
	{
		list->buf = ft_strdup("(null)");
		ft_precision_character(list);
		return (0);
	}
	len = ft_length_str(wchar);
	list->buf = (char *)malloc(sizeof(char) * len + 1);
	while (wchar[++i])
		ft_wchar_to_char(list, wchar[i], list->buf, &j);
	list->buf[j] = '\0';
	ft_precision_character(list);
	return (0);
}
