/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:30:57 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/27 23:34:29 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(t_cw_map *map, t_process *p)
{
	int			player;
	int			i;
	int			bot_count;
	t_bot		*cur_player;

	bot_count = map->num_players;
	i = -1;
	player = cw_get_dir_arg(map, cw_map_move(p->pc, 1), 0);
	while (++i < bot_count)
	{
		cur_player = map->players[i];
		if (cur_player->name == player)
		{
			cur_player->last_live_cycle = map->cur_cycle + 1;
			cur_player->lives_in_period++;
		}
	}
	p->is_alive = 1;
	map->lives_count++;
	return (1);
}

char		cw_fill_reg(t_cw_map *map, t_process *p, int regn, int i)
{
	int j;
	int	carry;

	carry = 0;
	if (cw_checkreg_num(regn))
	{
		j = 0;
		while (j < REG_SIZE)
		{
			carry = (carry << 8) + map->memory[i];
			p->reg[regn - 1][j++] = map->memory[i];
			i = cw_map_move(i, 1);
		}
		return (carry == 0) ? 1 : 0;
	}
	return (p->carry);
}

void		cw_load_aux(t_cw_map *map, t_process *p, int is_long)
{
	int				i;
	unsigned char	cbyte;
	int				cur;
	int				index;

	cur = cw_map_move(p->pc, 1);
	cbyte = map->memory[cur];
	cur = cw_map_move(p->pc, 2);
	if (((cbyte >> 6) & 3) == IND_CODE)
	{
		i = -1;
		index = 0;
		while (++i < IND_SIZE)
			index = (index << 8) + map->memory[cw_map_move(cur, i)];
		index = (short)index;
		index = (is_long) ? index : (index % IDX_MOD);
		p->carry = cw_fill_reg(map, p, map->memory[cw_map_move(cur,
				IND_SIZE)], cw_map_move(p->pc, index));
	}
	else if (((cbyte >> 6) & 3) == DIR_CODE)
		p->carry = cw_fill_reg(map, p,
			map->memory[cw_map_move(cur, DIR_SIZE)], cur);
}

int			cw_load(t_cw_map *map, t_process *p)
{
	cw_load_aux(map, p, 0);
	return (2);
}

int			cw_long_load(t_cw_map *map, t_process *p)
{
	cw_load_aux(map, p, 1);
	return (13);
}
