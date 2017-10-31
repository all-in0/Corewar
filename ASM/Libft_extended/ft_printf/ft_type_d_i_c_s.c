/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_d_i_c_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:19:18 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/02/24 16:01:12 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_base(intmax_t num, int base)
{
	char		*s;
	int			i;
	intmax_t	n;
	uintmax_t	number;

	n = num;
	i = (base == 10 && num < 0) ? 2 : 1;
	while (n /= base)
		i++;
	s = (char*)malloc(sizeof(char) * i + 1);
	s[i] = '\0';
	(base == 10 && num < 0) ? s[0] = '-' : 0;
	(num == 0) ? s[0] = '0' : 0;
	number = (num < 0) ? (uintmax_t)(-num) : (num);
	while (number)
	{
		((number % base) < 10) ? (s[--i] = (number % base) + 48)
		: (s[--i] = (number % base) + 87);
		number /= base;
	}
	return (s);
}

static char	*ft_mod_d_i(t_lst *list, va_list ap)
{
	intmax_t value;

	value = 0;
	if (list->mod[0] == 'z' && list->mod[1] != 'z')
		value = (intmax_t)(va_arg(ap, ssize_t));
	else if (list->mod[0] == 'j' && list->mod[1] != 'j')
		value = (intmax_t)(va_arg(ap, intmax_t));
	else if (list->mod[0] == 'h' && list->mod[1] != 'h' && list->type != 'D')
		value = (intmax_t)(short)(va_arg(ap, int));
	else if (list->mod[0] == 'h' && list->mod[1] == 'h' && list->type != 'D')
		value = (intmax_t)(char)(va_arg(ap, int));
	else if (list->mod[0] == 'l' && list->mod[1] != 'l' && list->type != 'D')
		value = (intmax_t)(va_arg(ap, long));
	else if (list->mod[0] == 'l' && list->mod[1] == 'l' && list->type != 'D')
		value = (intmax_t)(va_arg(ap, long long));
	else if (list->type == 'd' || list->type == 'i')
		value = (intmax_t)(va_arg(ap, int));
	else if (list->type == 'D')
		value = (intmax_t)(va_arg(ap, long));
	return (ft_itoa_base(value, 10));
}

int			ft_type_d_i(t_lst *list, va_list ap)
{
	list->buf = ft_mod_d_i(list, ap);
	ft_precision_digits(list);
	return (0);
}

int			ft_type_c_s(t_lst *list, va_list ap)
{
	char *str;
	char c;

	if (list->type == 's')
		list->buf =
	((str = va_arg(ap, char *)) == NULL) ? ft_strdup("(null)") : ft_strdup(str);
	else if (list->type == 'c' || list->type == 'C')
	{
		if ((c = (char)va_arg(ap, int)) == 0)
			list->buf = ft_strdup("\0");
		else
		{
			list->buf = (char*)malloc(2);
			list->buf[0] = c;
			list->buf[1] = '\0';
		}
	}
	else
	{
		list->buf = (char*)malloc(2);
		list->buf[0] = (char)va_arg(ap, int);
		list->buf[1] = '\0';
	}
	ft_precision_character(list);
	return (0);
}
