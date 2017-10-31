/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 04:37:42 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 12:16:45 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cw_print_winer(char *b_name, int cycle, int id)
{
	ft_printf("\nContestant %i : \"%s\" has won !!! ", id, b_name);
	ft_printf("Last said live on %i cycle.\n\n", cycle);
}

t_byte			cw_vm_stop(t_cw_map *map)
{
	int				player;
	int				p_ids[2];
	unsigned int	last_live;
	char			*bot_name;

	player = map->num_players;
	last_live = 0;
	ft_memset(p_ids, 0, sizeof(p_ids));
	p_ids[0] = 0;
	bot_name = NEW_S(char, PROG_NAME_LENGTH + 1);
	while (player--)
		if (map->players[player]->last_live_cycle >= last_live)
		{
			last_live = map->players[player]->last_live_cycle;
			p_ids[0] = map->players[player]->id;
			p_ids[1] = map->players[player]->last_live_cycle;
			ft_strcpy(bot_name, map->players[player]->header->prog_name);
		}
	(map->f_disp) ? cw_disp_winner(bot_name, p_ids[1], p_ids[0],
		cw_getnbr_byid(p_ids[0], map)) : cw_print_winer(bot_name,
		p_ids[1], p_ids[0]);
	free(bot_name);
	free_map(map);
	exit(1);
}

t_byte			cw_clean_process(t_cw_map *map)
{
	t_process	*pc_list;
	t_process	*tmp;

	pc_list = map->process;
	while (pc_list)
	{
		if ((!pc_list->is_alive))
		{
			tmp = pc_list->next;
			cw_suspend_process(map, pc_list->ps_id);
			pc_list = tmp;
		}
		else
		{
			pc_list->is_alive = 0;
			pc_list->num_lives = 0;
			pc_list = pc_list->next;
		}
	}
	return (1);
}

t_byte			cw_check_lives(t_cw_map *map)
{
	int		i;

	map->checks_perf++;
	cw_clean_process(map);
	if (map->checks_perf >= MAX_CHECKS || map->lives_count >= NBR_LIVE)
	{
		map->checks_perf = 0;
		map->cycle_to_die -= CYCLE_DELTA;
		if (map->cycle_to_die <= 0)
			cw_vm_stop(map);
	}
	map->next_check = map->cur_cycle + map->cycle_to_die;
	map->lives_count = 0;
	i = -1;
	while (map->players[++i])
		map->players[i]->lives_in_period = 0;
	return (1);
}

t_byte			cw_move_ps_pc(t_byte *style, t_process *ps, int pc_offset)
{
	int		refresh_pc;
	t_byte	cur_style;

	cur_style = style[ps->pc];
	style[ps->pc] = (cur_style == 100) ? (0) : (cw_get_swap_pair(cur_style, 0));
	refresh_pc = (ps->pc + pc_offset) % MEM_SIZE;
	ps->pc = (refresh_pc > -1) ? refresh_pc : (refresh_pc + MEM_SIZE);
	cur_style = style[ps->pc];
	style[ps->pc] = (cur_style == 0) ? (100) : (cw_get_swap_pair(cur_style, 4));
	return (1);
}
