/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ldi_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:30:47 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/27 23:30:49 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short		cw_ldi_first_arg(int *index, int c_oct, t_cw_map *map, t_process *p)
{
	int current;

	cw_refresh_index(index, *index, 1);
	if (((c_oct >> 6) & 3) == IND_CODE)
	{
		current = cw_get_ind_arg(map, p, *index);
		cw_refresh_index(index, *index, 2);
		return (current);
	}
	else if (((c_oct >> 6) & 3) == DIR_CODE)
	{
		current = cw_get_dir_arg(map, *index, 1);
		cw_refresh_index(index, *index, 2);
		return (current);
	}
	else if (((c_oct >> 6) & 3) == REG_CODE)
	{
		current = cw_get_reg_arg(map, p, *index);
		cw_refresh_index(index, *index, 1);
		return (current);
	}
	return (0);
}

void		cw_load_idx_aux(t_cw_map *map, t_process *p, int is_long)
{
	t_byte	c_oct;
	int		address[2];
	int		refresh;

	address[0] = cw_map_move(p->pc, 1);
	c_oct = map->memory[address[0]];
	address[1] = cw_ldi_first_arg(&address[0], c_oct, map, p);
	if (((c_oct >> 4) & 3) == DIR_CODE)
	{
		address[1] = address[1] + cw_get_dir_arg(map, address[0], 1);
		cw_refresh_index(&address[0], address[0], 2);
	}
	else if (((c_oct >> 4) & 3) == REG_CODE)
	{
		address[1] = address[1] + cw_get_reg_arg(map, p, address[0]);
		cw_refresh_index(&address[0], address[0], 1);
	}
	if (is_long)
		cw_refresh_index(&refresh, p->pc, address[1]);
	else
		cw_refresh_index(&refresh, p->pc, (address[1] % IDX_MOD));
	if (cw_checkreg_num(map->memory[address[0]]))
		p->carry = cw_fill_reg(map, p, map->memory[address[0]], refresh);
}

int			cw_load_idx(t_cw_map *map, t_process *p)
{
	cw_load_idx_aux(map, p, 0);
	return (10);
}

int			cw_long_load_idx(t_cw_map *map, t_process *p)
{
	cw_load_idx_aux(map, p, 1);
	return (14);
}
