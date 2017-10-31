/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_store_add_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:32:27 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 10:17:37 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_store(t_cw_map *map, t_process *p)
{
	int				cur;
	unsigned char	cbyte;

	cur = cw_map_move(p->pc, 1);
	cbyte = map->memory[cur];
	cur = cw_map_move(cur, 1);
	if (cw_checkreg_num(map->memory[cur]))
	{
		if (((cbyte >> 4) & 3) == REG_CODE)
			cw_cpy_reg(p, map->memory[cur], map->memory[cw_map_move(cur, 1)]);
		if (((cbyte >> 4) & 3) == IND_CODE)
			cw_putreg_onmap(map, p->reg[map->memory[cur] - 1],
				cw_map_move(p->pc, cw_get_ind_value(map,
					cw_map_move(cur, 1))), p);
	}
	return (3);
}

int			cw_add_sub_aux(t_cw_map *map, t_process *p, char l_op)
{
	int		byte[2];
	char	result;

	byte[0] = 0;
	byte[1] = 0;
	byte[0] = cw_map_move(p->pc, 2);
	result = cw_checkreg_num(map->memory[byte[0]]) &&
		cw_checkreg_num(map->memory[cw_map_move(byte[0], 1)]) &&
		cw_checkreg_num(map->memory[cw_map_move(byte[0], 2)]);
	if (!result)
		return (0);
	else
	{
		byte[1] = cw_get_reg_arg(map, p, byte[0]);
		byte[0] = cw_map_move(byte[0], 1);
		if (l_op == 'a')
			byte[1] += cw_get_reg_arg(map, p, byte[0]);
		else if (l_op == 's')
			byte[1] -= cw_get_reg_arg(map, p, byte[0]);
		byte[0] = cw_map_move(byte[0], 1);
		p->carry = cw_put_intin_reg(p, byte[1], map->memory[byte[0]]);
	}
	return (1);
}

int			cw_add(t_cw_map *map, t_process *p)
{
	cw_add_sub_aux(map, p, 'a');
	return (4);
}

int			cw_sub(t_cw_map *map, t_process *p)
{
	cw_add_sub_aux(map, p, 's');
	return (5);
}
