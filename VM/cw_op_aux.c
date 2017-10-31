/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_op_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:31:22 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/27 23:35:02 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_map_move(int cur_pos, int shift)
{
	int		new_pos;

	new_pos = (cur_pos + shift) % MEM_SIZE;
	return (new_pos >= 0 ? new_pos : new_pos + MEM_SIZE);
}

t_byte		cw_checkreg_num(t_byte reg_num)
{
	return ((reg_num && reg_num <= REG_NUMBER) ? 1 : 0);
}

int			get_arg_mask(int a_type)
{
	if (a_type == 1)
		return (T_REG);
	else if (a_type == 2)
		return (T_DIR);
	else if (a_type == 3)
		return (T_IND);
	return (BAD_ARG_MASK);
}

int			get_arg_size(unsigned short a_mask, unsigned int l_size)
{
	if (a_mask == 1)
		return (1);
	else if (a_mask == 2)
		return (2 + 2 * l_size);
	else if (a_mask == 4)
		return (2);
	return (0);
}

int			get_max_arg_size(unsigned short a_mask, t_op *op)
{
	int		n;
	int		i;

	i = -1;
	n = op->num_args;
	while (++i < n)
	{
		if (((op->arg_mask[i]) & a_mask) == a_mask)
			return (get_arg_size(a_mask, op->label_size));
	}
	return (get_arg_size(a_mask, 1));
}
