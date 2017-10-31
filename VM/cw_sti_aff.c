/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:31:48 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 01:17:33 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_sti_first_arg(int *index, int c_oct, t_cw_map *map,
	t_process *p)
{
	int		current;

	if (((c_oct >> 4) & 3) == IND_CODE)
	{
		current = cw_get_ind_arg(map, p, *index);
		cw_refresh_index(index, *index, 2);
		return (current);
	}
	else if (((c_oct >> 4) & 3) == DIR_CODE)
	{
		current = cw_get_dir_arg(map, *index, 1);
		cw_refresh_index(index, *index, 2);
		return (current);
	}
	else if (((c_oct >> 4) & 3) == REG_CODE)
	{
		current = cw_get_reg_arg(map, p, *index);
		cw_refresh_index(index, *index, 1);
		return (current);
	}
	return (0);
}

int			cw_store_idx(t_cw_map *map, t_process *p)
{
	int		index;
	int		address;
	int		refresher;
	t_byte	c_oct;
	int		s_arg;

	address = 0;
	cw_refresh_index(&index, p->pc, 1);
	cw_refresh_index(&refresher, index, 1);
	c_oct = map->memory[index];
	if (cw_checkreg_num(map->memory[refresher]))
	{
		cw_refresh_index(&refresher, refresher, 1);
		address = cw_sti_first_arg(&refresher, c_oct, map, p);
		s_arg = 0;
		if (((c_oct >> 2) & 3) == DIR_CODE)
			s_arg = cw_get_dir_arg(map, refresher, 1);
		else if (((c_oct >> 2) & 3) == REG_CODE)
			s_arg = cw_get_reg_arg(map, p, refresher);
		address += s_arg;
		cw_refresh_index(&refresher, p->pc, 2);
		cw_refresh_index(&index, p->pc, (address % IDX_MOD));
		cw_putreg_onmap(map, p->reg[map->memory[refresher] - 1], index, p);
	}
	return (11);
}

int			cw_aff(t_cw_map *map, t_process *p)
{
	int		index;
	t_byte	reg_num;
	int		value;

	value = 0;
	cw_refresh_index(&index, p->pc, 2);
	reg_num = map->memory[index];
	if (cw_checkreg_num(reg_num))
	{
		index = -1;
		while (++index < REG_SIZE)
			value = (value << 8) + p->reg[reg_num - 1][index];
		attron(COLOR_PAIR(0));
		mvprintw(59, 220, "AFF BOX");
		attroff(COLOR_PAIR(0));
		attron(COLOR_PAIR(p->parent));
		cw_debug_msgbox_aff(value);
		attroff(COLOR_PAIR(p->parent));
	}
	return (16);
}
