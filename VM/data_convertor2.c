/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_convertor2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 04:25:37 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 05:33:39 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_getnbr_byid(int id, t_cw_map *map)
{
	int		bot_count;

	bot_count = map->num_players;
	while (--bot_count >= 0)
	{
		if (map->players[bot_count]->id == id)
			return (map->players[bot_count]->name);
	}
	return (0);
}

void		reverse_bytes(int *bytes, int size)
{
	unsigned int	res;
	int				i;
	unsigned int	old_res;

	old_res = *bytes;
	i = -1;
	res = 0;
	while (++i < size)
		res = res | (((old_res << (8 * i)) >> 8 * (size - 1)) << (i * 8));
	(*bytes) = res;
}

t_byte		cw_refresh_index(int *updatable, int updater, int concatenator)
{
	*updatable = (updater + concatenator) % MEM_SIZE;
	*updatable = (*updatable < 0) ? *updatable + MEM_SIZE : *updatable;
	return (1);
}

void		cw_cpy_regs(unsigned char (*reg)[REG_SIZE],
	unsigned char reg_p[REG_SIZE])
{
	int		i;

	i = -1;
	while (++i < REG_SIZE)
		(*reg)[i] = reg_p[i];
}

void		cw_set_reg_rev(unsigned char (*reg)[REG_SIZE], int bot_name)
{
	int		i;

	i = -1;
	while (++i < REG_SIZE)
		(*reg)[i] = (bot_name >> (8 * (REG_SIZE - i - 1)));
}
