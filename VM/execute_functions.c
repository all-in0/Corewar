/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:14:10 by idemchen          #+#    #+#             */
/*   Updated: 2017/10/28 04:37:20 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op g_op_tab[];

t_op			*get_instr(unsigned short int op_code)
{
	int		i;

	i = -1;
	while (++i < NUM_CMDS)
	{
		if (g_op_tab[i].op_code == op_code)
			return (&(g_op_tab[i]));
	}
	return (NULL);
}

t_byte			cw_invoke_instr(int op_code, t_cw_map *map, t_process *ps)
{
	static int		(*instr_functs[NUM_CMDS - 1])(t_cw_map*, t_process*) =
	{cw_live, cw_load, cw_store, cw_add,
		cw_sub, cw_and, cw_or, cw_xor, cw_zjump,
		cw_load_idx, cw_store_idx, cw_fork, cw_long_load,
		cw_long_load_idx, cw_long_fork,
		cw_aff};

	(*instr_functs[op_code - 1])(map, ps);
	return (1);
}

static void		refresh_execute(t_cw_map *map, t_process *ps,
	int *ok_flag, int *pc_shift)
{
	if ((*ok_flag = cw_getpc_shift(map->memory,
				ps->pc, &(g_op_tab[ps->cur_op - 1]), pc_shift)))
	{
		cw_invoke_instr(ps->cur_op, map, ps);
		if (ps->cur_op != 9)
			cw_move_ps_pc(map->mem_style, ps, *pc_shift);
		refresh();
	}
	else
	{
		cw_move_ps_pc(map->mem_style, ps, *pc_shift);
		refresh();
	}
}

t_byte			cw_execute_instr(t_cw_map *map, t_process *ps)
{
	t_byte		op_c;
	int			pc_shift;
	int			ok_flag;

	op_c = map->memory[ps->pc];
	if (ps->wait != WT_UNSET && ps->wait > 1)
		return (ps->wait -= 1);
	if (ps->cur_op != 0 || (op_c >= 1 && op_c < NUM_CMDS))
	{
		if (ps->cur_op == 0)
			ps->cur_op = op_c;
		if (ps->wait == 1)
		{
			refresh_execute(map, ps, &ok_flag, &pc_shift);
			ps->cur_op = 0;
			return ((ps->wait = WT_UNSET));
		}
		if (ps->wait == WT_UNSET)
			return ((ps->wait = g_op_tab[ps->cur_op - 1].cycle_cost - 1));
	}
	if (ps->wait >= 0)
		cw_move_ps_pc(map->mem_style, ps, 1);
	return (1);
}

t_byte			cw_execute_process(t_cw_map *map)
{
	t_process	*process;

	if ((process = map->process) == NULL)
		cw_vm_stop(map);
	while (process)
	{
		cw_execute_instr(map, process);
		process = process->next;
	}
	return (1);
}
