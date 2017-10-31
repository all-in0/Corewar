/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_op_shift_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:31:33 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/27 23:35:39 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_byte					cw_getpc_shift_aux(t_op *op,
	t_byte a_types[MAX_N_ARGS], int *shift)
{
	int					i;
	unsigned short		a_mask;
	int					n;
	t_byte				f;

	i = -1;
	i = -1;
	f = 1;
	n = op->num_args;
	while (++i < n)
	{
		a_mask = get_arg_mask(a_types[i]);
		if (((op->arg_mask[i]) & a_mask) == a_mask)
			(*shift) += get_arg_size(a_mask, op->label_size);
		else
		{
			f = 0;
			(*shift) += get_max_arg_size(a_mask, op);
		}
	}
	return (f);
}

t_byte					cw_getpc_shift(t_byte *mem, int pc, t_op *op,
	int *shift)
{
	int					n;
	t_byte				a_types[MAX_N_ARGS];
	int					c_octal;
	t_byte				ok_flag;

	n = op->num_args;
	c_octal = (op->codage_octal) ? (int)mem[cw_map_move(pc, 1)] : 128;
	(*shift) = (op->codage_octal) ? 2 : 1;
	while (n--)
		a_types[n] = (((c_octal << (n * 2 + 23)) & 2147483647) >> 29);
	ok_flag = cw_getpc_shift_aux(op, a_types, shift);
	return (ok_flag);
}

void					cw_cpy_reg(t_process *proc, unsigned char r1,
	unsigned char r2)
{
	int	j;

	if (cw_checkreg_num(r1) && cw_checkreg_num(r2))
	{
		j = -1;
		while (++j < REG_SIZE)
			proc->reg[r2 - 1][j] = proc->reg[r1 - 1][j];
	}
}

void					cw_putreg_onmap(t_cw_map *map, unsigned char *reg,
	int i, t_process *p)
{
	int	j;

	j = -1;
	while (++j < REG_SIZE)
	{
		cw_highlight_color(map->mem_style, cw_map_move(i, j), p->parent);
		map->memory[cw_map_move(i, j)] = reg[j];
	}
}
