/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:02:27 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/02/24 20:04:19 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_zero(t_lst *list)
{
	if (list->precision == -1 && !(list->flags[5] == '#'
				&& (list->type == 'o' || list->type == 'O'
					|| list->type == 'p')))
		list->buf = "\0";
	return (1);
}

void	ft_funcs_arr(t_lst *list)
{
	list->g_funcs['c'] = &ft_type_c_s;
	list->g_funcs['C'] = &ft_type_c_s;
	list->g_funcs['s'] = &ft_type_c_s;
	list->g_funcs['S'] = &ft_type_big_s;
	list->g_funcs['p'] = &ft_type_p;
	list->g_funcs['d'] = &ft_type_d_i;
	list->g_funcs['D'] = &ft_type_d_i;
	list->g_funcs['i'] = &ft_type_d_i;
	list->g_funcs['o'] = &ft_type_u_o_x;
	list->g_funcs['O'] = &ft_type_big_u_o;
	list->g_funcs['u'] = &ft_type_u_o_x;
	list->g_funcs['U'] = &ft_type_big_u_o;
	list->g_funcs['x'] = &ft_type_u_o_x;
	list->g_funcs['X'] = &ft_type_u_o_x;
}

void	ft_structure_zero(t_lst *list)
{
	int i;

	i = -1;
	list->buf = NULL;
	while (++i < 6)
		(list->flags)[i] = 0;
	list->width = 0;
	list->precision = 0;
	(list->mod)[0] = 0;
	(list->mod)[1] = 0;
	list->type = 0;
}

int		ft_flags(char *f, t_lst *list)
{
	int j;

	j = 0;
	while (ft_strchr("-+ #0", f[++list->i]))
		(list->flags[f[list->i] % 6] = f[list->i]);
	while (f[list->i] >= 48 && f[list->i] <= 57)
		list->width = (list->width * 10) + (f[list->i++]) - 48;
	if (f[list->i] == '.')
	{
		while (f[(++list->i)] >= 48 && f[list->i] <= 57)
			list->precision = (list->precision * 10) + f[list->i] - 48;
		(list->precision == 0) ? list->precision = -1 : 0;
	}
	while (f[list->i] == 'h' || f[list->i] == 'l'
			|| f[list->i] == 'j' || f[list->i] == 'z')
		list->mod[j++ % 2] = f[list->i++];
	if (!(ft_strchr("sSpdDioOuUxXcC", f[list->i])) && f[list->i] != 32)
	{
		list->buf = (char*)malloc(2);
		list->buf[0] = f[list->i];
		list->buf[1] = '\0';
		ft_precision_character(list);
	}
	return ((ft_strchr("sSpdDioOuUxXcC", f[list->i]))
			? list->type = f[list->i] : 0);
}

int		ft_printf(const char *format, ...)
{
	t_lst	list;
	va_list	ap;

	list.i = -1;
	va_start(ap, format);
	ft_funcs_arr(&list);
	list.counter = 0;
	while (format[++list.i])
	{
		if (format[list.i] == '%')
		{
			if (format[list.i + 1] == '\0')
				return (0);
			ft_structure_zero(&list);
			if (ft_flags((char*)format, &list) > 0)
				list.g_funcs[(int)list.type](&list, ap);
		}
		else
			list.counter += write(1, &format[list.i], 1);
	}
	va_end(ap);
	return (list.counter);
}
