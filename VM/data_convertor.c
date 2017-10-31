/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_convertor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 00:09:00 by vnakonec          #+#    #+#             */
/*   Updated: 2017/10/28 10:12:58 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_get_dir_arg(t_cw_map *map, int current_index, int is_short)
{
	int		shifts[3];
	int		size;
	short	s_res;

	shifts[0] = -1;
	shifts[1] = 0;
	shifts[2] = 0;
	size = (is_short) ? 2 : DIR_SIZE;
	while (++shifts[0] < size)
	{
		cw_refresh_index(&shifts[2], current_index, shifts[0]);
		shifts[1] = shifts[1] << 8;
		shifts[1] = shifts[1] + map->memory[shifts[2]];
	}
	s_res = (short)shifts[1];
	if (is_short)
		return (s_res);
	return (shifts[1]);
}

short		cw_get_ind_value(t_cw_map *map, int cur)
{
	int		oper[2];
	int		short_address;

	oper[0] = -1;
	oper[1] = 0;
	while (++oper[0] < IND_SIZE)
		oper[1] = (oper[1] << 8) + map->memory[cw_map_move(cur, oper[0])];
	short_address = (short)oper[1] % IDX_MOD;
	return (short_address);
}

int			cw_get_ind_arg(t_cw_map *map, t_process *p, int cur)
{
	int		oper[4];
	short	short_adress;

	oper[0] = -1;
	oper[1] = 0;
	oper[2] = 0;
	oper[3] = 0;
	short_adress = 0;
	while (++oper[0] < IND_SIZE)
	{
		oper[3] = cw_map_move(cur, oper[0]);
		oper[1] = (oper[1] << 8);
		oper[1] = oper[1] + map->memory[oper[3]];
	}
	short_adress = (short)oper[1] % IDX_MOD;
	oper[0] = -1;
	oper[3] = 0;
	while (++oper[0] < REG_SIZE)
	{
		oper[3] = cw_map_move(p->pc, short_adress + oper[0]);
		oper[2] = oper[2] << 8;
		oper[2] = oper[2] + map->memory[oper[3]];
	}
	return (oper[2]);
}

int			cw_get_reg_arg(t_cw_map *map, t_process *p, int current_index)
{
	int		shifts[3];

	shifts[0] = -1;
	shifts[1] = 0;
	shifts[2] = 0;
	if (cw_checkreg_num(map->memory[current_index]))
		while (++shifts[0] < REG_SIZE)
		{
			shifts[1] = shifts[1] << 8;
			shifts[1] = shifts[1] +
				p->reg[map->memory[current_index] - 1][shifts[0]];
		}
	return (shifts[1]);
}

t_byte		cw_put_intin_reg(t_process *p, int value, t_byte regn)
{
	int		i;
	int		carry;

	if (cw_checkreg_num(regn))
	{
		carry = (value == 0) ? 1 : 0;
		i = REG_SIZE;
		while (--i >= 0)
		{
			p->reg[regn - 1][i] = value;
			value = (value >> 8);
		}
		return (carry);
	}
	return (p->carry);
}
