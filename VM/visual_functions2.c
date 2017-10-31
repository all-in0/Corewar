/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 04:30:21 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 04:30:22 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_byte			cw_highlight_color(t_byte *style, int pos, int pair)
{
	style[pos] = pair + 8;
	return (1);
}

t_byte			cw_get_swap_pair(t_byte pair, t_byte pair_offset)
{
	t_byte		res;
	t_byte		res_ret;

	if (pair == 100 || pair == 0)
		return (pair);
	res = pair % 4;
	res_ret = (res == 0) ? (4 + pair_offset) : (res + pair_offset);
	return (res_ret);
}

void			cw_put_proc_style(unsigned char *style, t_process *ps)
{
	while (ps)
	{
		if ((style[ps->pc] >= 5 && style[ps->pc] <= 8) || style[ps->pc] == 100)
			ps = ps->next;
		else
		{
			style[ps->pc] = (style[ps->pc] == 0) ?
				100 : (cw_get_swap_pair(style[ps->pc], 4));
			ps = ps->next;
		}
	}
}

static void		init_color_pairs(int (*first)[4][3], int (*second)[4][3])
{
	(*first)[0][0] = 130;
	(*first)[0][1] = 630;
	(*first)[0][2] = 145;
	(*first)[1][0] = 700;
	(*first)[1][1] = 145;
	(*first)[1][2] = 145;
	(*first)[2][0] = 196;
	(*first)[2][1] = 400;
	(*first)[2][2] = 710;
	(*first)[3][0] = 755;
	(*first)[3][1] = 750;
	(*first)[3][2] = 180;
	(*second)[0][0] = 420;
	(*second)[0][1] = 937;
	(*second)[0][2] = 431;
	(*second)[1][0] = 1000;
	(*second)[1][1] = 515;
	(*second)[1][2] = 515;
	(*second)[2][0] = 515;
	(*second)[2][1] = 715;
	(*second)[2][2] = 1000;
	(*second)[3][0] = 1000;
	(*second)[3][1] = 1000;
	(*second)[3][2] = 485;
}

void			init_bot_colors(int n_bots)
{
	int		m_c[4][3];
	int		h_c[4][3];
	int		*rgb_c;
	int		*rgb_h;

	init_color_pairs(&m_c, &h_c);
	n_bots++;
	while (n_bots-- > 1)
	{
		rgb_c = m_c[n_bots - 1];
		rgb_h = h_c[n_bots - 1];
		init_color(100 + n_bots, rgb_c[0], rgb_c[1], rgb_c[2]);
		init_color(104 + n_bots, rgb_h[0], rgb_h[1], rgb_h[2]);
		init_pair(n_bots, 100 + n_bots, COLOR_BLACK);
		init_pair(n_bots + 4, COLOR_BLACK, 100 + n_bots);
		init_pair(n_bots + 8, 104 + n_bots, COLOR_BLACK);
	}
}
