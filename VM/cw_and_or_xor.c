/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:30:35 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/27 23:30:37 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_and_or_xor_get_arg(t_cw_map *map, t_process *p,
	int **curr_idx, int cb_shift)
{
	int		*elems;
	int		arg;

	elems = *curr_idx;
	arg = 0;
	if (((elems[1] >> cb_shift) & 3) == REG_CODE)
	{
		arg = cw_get_reg_arg(map, p, elems[0]);
		elems[0] = cw_map_move(elems[0], 1);
	}
	else if (((elems[1] >> cb_shift) & 3) == DIR_CODE)
	{
		arg = cw_get_dir_arg(map, elems[0], 0);
		elems[0] = cw_map_move(elems[0], 4);
	}
	else if (((elems[1] >> cb_shift) & 3) == IND_CODE)
	{
		arg = cw_get_ind_arg(map, p, elems[0]);
		elems[0] = cw_map_move(elems[0], 2);
	}
	return (arg);
}

void		cw_and_or_xor_aux(t_cw_map *map, t_process *p,
	int (*curr_idx)[], char l_op)
{
	int *elements;
	int	s_arg;

	elements = *curr_idx;
	elements[2] = cw_and_or_xor_get_arg(map, p, &elements, 6);
	s_arg = cw_and_or_xor_get_arg(map, p, &elements, 4);
	if (l_op == 'a')
		elements[2] &= s_arg;
	else if (l_op == 'o')
		elements[2] |= s_arg;
	else if (l_op == 'x')
		elements[2] ^= s_arg;
}

int			cw_and(t_cw_map *map, t_process *p)
{
	int		byte[3];

	byte[0] = 0;
	byte[1] = 0;
	byte[2] = 0;
	byte[0] = cw_map_move(p->pc, 2);
	byte[1] = map->memory[cw_map_move(p->pc, 1)];
	cw_and_or_xor_aux(map, p, &byte, 'a');
	p->carry = cw_put_intin_reg(p, byte[2], map->memory[byte[0]]);
	return (6);
}

int			cw_or(t_cw_map *map, t_process *p)
{
	int		byte[3];

	byte[0] = 0;
	byte[1] = 0;
	byte[2] = 0;
	byte[0] = cw_map_move(p->pc, 2);
	byte[1] = map->memory[cw_map_move(p->pc, 1)];
	cw_and_or_xor_aux(map, p, &byte, 'o');
	p->carry = cw_put_intin_reg(p, byte[2], map->memory[byte[0]]);
	return (7);
}

int			cw_xor(t_cw_map *map, t_process *p)
{
	int byte[3];

	byte[0] = 0;
	byte[1] = 0;
	byte[2] = 0;
	byte[0] = cw_map_move(p->pc, 2);
	byte[1] = map->memory[cw_map_move(p->pc, 1)];
	cw_and_or_xor_aux(map, p, &byte, 'x');
	p->carry = cw_put_intin_reg(p, byte[2], map->memory[byte[0]]);
	return (8);
}
