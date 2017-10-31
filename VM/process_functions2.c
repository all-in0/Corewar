/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 05:20:46 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 05:39:23 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	void	iterate_list(t_process **prev, int ps_id)
{
	while ((*prev)->next)
	{
		if ((*prev)->next->ps_id == ps_id)
			break ;
		(*prev) = (*prev)->next;
	}
}

void			cw_suspend_process(t_cw_map *map, int ps_id)
{
	t_process	*prev;
	t_byte		cur_style;

	if (map->process == NULL)
		return ;
	if (map->process->ps_id == ps_id)
	{
		push_process(&(map->suspended_proc), pop_top_process(&(map->process)));
		return ;
	}
	prev = map->process;
	iterate_list(&prev, ps_id);
	if (prev->next != NULL)
	{
		cur_style = map->mem_style[prev->next->pc];
		map->mem_style[prev->next->pc] = (cur_style == 100) ?
			(0) : (cw_get_swap_pair(cur_style, 0));
		push_process(&(map->suspended_proc), pop_process(&prev));
	}
	else
	{
		map->error_msg = "Suspend process ERROR. You SHOULD NEVER see this";
		return ;
	}
	map->proc_count--;
}

void			set_reg_data(int bot_nbr, t_process *pp, t_process *np)
{
	int			i;

	i = 0;
	if (pp == NULL)
		cw_set_reg_rev(&(np->reg[i]), bot_nbr);
	else
		cw_cpy_regs(&(np->reg[i]), pp->reg[i]);
	while (++i < REG_NUMBER)
	{
		if (pp == NULL)
			cw_set_reg_rev(&(np->reg[i]), 0);
		else
			cw_cpy_regs(&(np->reg[i]), pp->reg[i]);
	}
}

void			create_process(t_cw_map *map, t_process *pp,
		int bot_id, int offset)
{
	t_process	*np;
	static int	ps_id = 0;

	if (map->suspended_proc)
		np = pop_top_process(&(map->suspended_proc));
	else
	{
		np = NEW(t_process);
		np->ps_id = ps_id++;
	}
	map->proc_count++;
	np->wait = WT_UNSET;
	np->parent = (pp == NULL) ? (bot_id + 1) : pp->parent;
	if (pp == NULL)
		set_reg_data(cw_getnbr_byid(bot_id + 1, map), NULL, np);
	else
		set_reg_data(0, pp, np);
	np->pc = offset;
	np->carry = (pp == NULL) ? 0 : pp->carry;
	np->is_alive = (pp == NULL) ? 0 : pp->is_alive;
	np->num_lives = 0;
	np->cur_op = 0;
	push_process(&(map->process), np);
}
