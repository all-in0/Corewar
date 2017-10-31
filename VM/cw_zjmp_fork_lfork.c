/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:41:43 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/27 23:28:51 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op g_op_tab[];

short		cw_pcjump_length(t_cw_map *map, t_process *p)
{
	int		size;
	int		bytes;
	int		map_pos;

	size = 0;
	bytes = size;
	while (++size <= IND_SIZE)
	{
		bytes = bytes << 8;
		map_pos = cw_map_move(p->pc, size);
		bytes = bytes + map->memory[map_pos];
	}
	return (bytes);
}

int			cw_zjump(t_cw_map *map, t_process *p)
{
	int		pc_jump;
	int		refresher;

	pc_jump = cw_pcjump_length(map, p);
	if (!p->carry)
		refresher = 3;
	else
		refresher = pc_jump % IDX_MOD;
	cw_move_ps_pc(map->mem_style, p, refresher);
	refresh();
	return (9);
}

int			cw_fork_lfork_aux(t_cw_map *map, t_process *p, int is_long)
{
	int			new_pc;
	t_process	*head;

	new_pc = cw_pcjump_length(map, p);
	new_pc = (is_long) ?
		cw_map_move(p->pc, new_pc) : cw_map_move(p->pc, new_pc % IDX_MOD);
	create_process(map, p, p->parent, new_pc);
	head = map->process;
	if ((!(map->mem_style[head->pc] >= 5 && map->mem_style[head->pc] <= 8) &&
		map->mem_style[head->pc] != 100) ||
		map->mem_style[head->pc] == 0)
		map->mem_style[head->pc] = (map->mem_style[head->pc] == 0) ?
			100 : (map->mem_style[head->pc] + 4);
	return (1);
}

int			cw_fork(t_cw_map *map, t_process *p)
{
	cw_fork_lfork_aux(map, p, 0);
	return (12);
}

int			cw_long_fork(t_cw_map *map, t_process *p)
{
	cw_fork_lfork_aux(map, p, 1);
	return (15);
}
