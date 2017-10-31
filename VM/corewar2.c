/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 04:42:06 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 04:42:07 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_show_dump_mem(t_cw_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (map->memory)
	{
		while (++i < MEM_SIZE)
		{
			if (j == -1)
			{
				ft_printf("0x0000 : ");
				j += 2;
			}
			if (i && ((i) % 64) == 0)
				ft_printf("%#.4x : ", j++ * 64);
			ft_printf("%.2x ", map->memory[i]);
			if (((i + 1) % 64) == 0)
				ft_putchar('\n');
		}
	}
}

t_byte		cw_show_dump(t_cw_map *map)
{
	if (map->f_disp)
	{
		endwin();
		curs_set(1);
	}
	cw_show_dump_mem(map);
	free_map(map);
	exit(1);
}

void		cw_adjust_cps(t_byte keycode, unsigned short *cps)
{
	if (keycode == 45)
	{
		if ((*cps) > 5)
			(*cps)--;
	}
	else if (keycode == 43)
	{
		if ((*cps) < 2000)
			(*cps)++;
	}
	else if (keycode == 47)
	{
		if ((*cps) > 15)
			(*cps) -= 10;
	}
	else if (keycode == 42)
	{
		if ((*cps) < 1990)
			(*cps) += 10;
	}
}
