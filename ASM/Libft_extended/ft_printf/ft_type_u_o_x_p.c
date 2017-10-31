/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_u_o_x_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:08:34 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/02/24 19:36:36 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_base_uintmax(uintmax_t num, int base)
{
	char		*s;
	int			i;
	uintmax_t	n;

	n = num;
	i = 1;
	while (n /= base)
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	if (num == 0)
		s[0] = '0';
	while (num)
	{
		((num % base) < 10) ? (s[--i] = (num % base) + 48)
		: (s[--i] = (num % base) + 87);
		num /= base;
	}
	return (s);
}

static char	*ft_mod_u_o_x(t_lst *list, va_list ap)
{
	uintmax_t value;

	value = 0;
	if (list->mod[0] == 'z' && list->mod[1] != 'z')
		value = (uintmax_t)(va_arg(ap, size_t));
	else if (list->mod[0] == 'j' && list->mod[1] != 'j')
		value = (uintmax_t)(va_arg(ap, uintmax_t));
	else if (list->mod[0] == 'h' && list->mod[1] != 'h')
		value = (uintmax_t)(unsigned short)(va_arg(ap, unsigned));
	else if (list->mod[0] == 'h' && list->mod[1] == 'h')
		value = (uintmax_t)(unsigned char)(va_arg(ap, unsigned));
	else if (list->mod[0] == 'l' && list->mod[1] != 'l')
		value = (uintmax_t)(va_arg(ap, unsigned long));
	else if (list->mod[0] == 'l' && list->mod[1] == 'l')
		value = (uintmax_t)(va_arg(ap, unsigned long long));
	else if (ft_strchr("xXuo", list->type))
		value = (uintmax_t)(va_arg(ap, unsigned));
	if (list->type == 'x' || list->type == 'X')
		return (ft_itoa_base_uintmax(value, 16));
	else if (list->type == 'o')
		return (ft_itoa_base_uintmax(value, 8));
	else
		return (ft_itoa_base_uintmax(value, 10));
}

int			ft_type_big_u_o(t_lst *list, va_list ap)
{
	uintmax_t value;

	value = (uintmax_t)(va_arg(ap, unsigned long));
	if (list->type == 'U')
		list->buf = ft_itoa_base_uintmax(value, 10);
	else if (list->type == 'O')
		list->buf = ft_itoa_base_uintmax(value, 8);
	ft_precision_digits(list);
	return (0);
}

int			ft_type_u_o_x(t_lst *list, va_list ap)
{
	list->buf = ft_mod_u_o_x(list, ap);
	(list->type == 'X') ? list->buf = ft_uppercase(list->buf) : 0;
	ft_precision_digits(list);
	return (0);
}

int			ft_type_p(t_lst *list, va_list ap)
{
	list->buf = ft_itoa_base_uintmax((uintmax_t)(va_arg(ap, void *)), 16);
	ft_precision_digits(list);
	return (0);
}
