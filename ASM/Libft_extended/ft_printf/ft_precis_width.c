/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precis_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:17:17 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/02/24 19:12:35 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_check_for_width(t_lst *list, int k)
{
	(ft_strchr(list->buf, '+')) ? *ft_strchr(list->buf, '+') = '0' : 0;
	(list->flags[1] == '+') ? list->buf[0] = '+' : 0;
	if (ft_strchr(list->buf, '-'))
	{
		*ft_strchr(list->buf, '-') = '0';
		list->buf[0] = '-';
	}
	if (list->flags[0] == 48)
	{
		(list->flags[5] == '#' && list->type == 'x' && k == 0) ?
		*ft_strchr(list->buf, 'x') = '0' : 0;
		(list->flags[5] == '#' && list->type == 'x' && k == 0) ?
		list->buf[1] = 'x' : 0;
		(list->flags[5] == '#' && list->type == 'X' && k == 0) ?
		*ft_strchr(list->buf, 'X') = '0' : 0;
		(list->flags[5] == '#' && list->type == 'X' && k == 0) ?
		list->buf[1] = 'X' : 0;
		(ft_strchr("dDi", list->type) && list->flags[2] == ' ') ?
		list->buf[0] = ' ' : 0;
		(list->type == 'p') ? *ft_strchr(list->buf, 'x') = '0' : 0;
		(list->type == 'p') ? list->buf[1] = 'x' : 0;
	}
	return (list->buf);
}

static void		ft_width(t_lst *l, int k, int flag)
{
	int		n_len[2];
	char	*s;

	n_len[1] = ft_strlen(l->buf);
	if (l->width > n_len[1])
	{
		n_len[0] = l->width - n_len[1];
		s = (char*)malloc(sizeof(char) * (n_len[0] + 1));
		if ((s[n_len[0]] = 0) || (l->flags[0] == '0' && l->flags[3] != '-'
			&& ((ft_strchr("pdioxXuU", l->type) && l->precision == 0)
				|| (ft_strchr("sScC", l->type)))))
			while (--n_len[0] >= 0)
				s[n_len[0]] = '0';
		else
			while (--n_len[0] >= 0)
				s[n_len[0]] = 32;
		l->buf = (l->flags[3] == '-') ? ft_strjoin(l->buf, s)
		: ft_strjoin(s, l->buf);
		(l->flags[0] == '0' || l->flags[5] == '#') ?
		l->buf = ft_check_for_width(l, k) : 0;
		free(s);
	}
	(flag == 1) ? (l->buf[ft_strlen(l->buf) - 1] = 0)
	|| (l->counter += write(1, l->buf, ft_strlen(l->buf) + 1)) :
		(l->counter += write(1, l->buf, ft_strlen(l->buf)));
}

static void		ft_other_flags(t_lst *list, int k, int flag)
{
	if (list->type == 'p')
		list->buf = ft_strjoin("0x", list->buf);
	if (list->flags[5] == '#' && ft_strchr("xX", list->type) && k == 0)
		((*ft_strchr("xX", list->type)) == 'x')
	? (list->buf = ft_strjoin("0x", list->buf))
			: (list->buf = ft_strjoin("0X", list->buf));
	if (list->flags[5] == '#' && ft_strchr("oO", list->type)
		&& list->precision == 0 && k == 0)
		list->buf = ft_strjoin("0", list->buf);
	if (list->flags[1] == '+' && ft_strchr("dDi", list->type)
		&& list->buf[0] != '-')
		list->buf = ft_strjoin("+", list->buf);
	if (list->flags[2] == ' ' && list->flags[1] != '+'
		&& list->type != 0 && list->buf[0] != '-'
		&& (list->width == 0 || list->precision > 0))
		ft_strchr("dDi", list->type) ?
	(list->buf = ft_strjoin(" ", list->buf)) : 0;
	ft_width(list, k, flag);
}

void			ft_precision_character(t_lst *list)
{
	int len;
	int flag;

	len = (int)ft_strlen(list->buf);
	flag = 0;
	if (list->type == 's' && list->precision < len && list->precision != 0)
	{
		(list->precision == -1) ? list->precision = 0 : 0;
		list->buf = ft_strsub(list->buf, 0, list->precision);
	}
	else if ((list->type == 'c' || list->type == 'C') && list->buf[0] == 0)
		flag = 1;
	ft_other_flags(list, 0, flag);
}

void			ft_precision_digits(t_lst *l)
{
	int		n_len_k[3];
	char	*s;

	n_len_k[1] = (int)ft_strlen(l->buf);
	if ((n_len_k[2] = 0) || (l->buf[0] == 48))
		n_len_k[2] = ft_zero(l);
	(l->precision == -1) ? l->precision = 0 : 0;
	if (l->precision > n_len_k[1])
	{
		n_len_k[0] = (l->buf[0] == '-') ? l->precision - n_len_k[1] + 1
		: l->precision - n_len_k[1];
		s = (char*)malloc(sizeof(char) * n_len_k[0] + 1);
		s[n_len_k[0]] = '\0';
		while (--n_len_k[0] >= 0)
			s[n_len_k[0]] = '0';
		if ((l->buf[0] == '-') && (l->buf = ft_strjoin(s, l->buf)))
		{
			*ft_strchr(l->buf, '-') = '0';
			l->buf[0] = '-';
		}
		else
			l->buf = ft_strjoin(s, l->buf);
		free(s);
	}
	ft_other_flags(l, n_len_k[2], 0);
}
