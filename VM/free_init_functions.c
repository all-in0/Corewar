/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 00:38:09 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 00:40:21 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			free_process(t_process *proc)
{
	t_process	*cur_proc;

	while (proc)
	{
		cur_proc = proc;
		proc = proc->next;
		free(cur_proc);
	}
}

void			free_map(t_cw_map *map)
{
	int			i;

	i = -1;
	free(map->memory);
	free(map->mem_style);
	free_process(map->process);
	free_process(map->suspended_proc);
	while (++i < map->num_players)
	{
		if (i < map->num_bots_init)
			free(map->players[i]->header);
		free(map->players[i]);
	}
	if (map->error_msg)
		free(map->error_msg);
	free(map->players);
}

void			check_malloc(t_cw_map *map)
{
	int			nbr;

	if (!(map->memory))
		error_call("Map->Memory malloc has failed");
	if (!(map->mem_style))
		error_call("Map->Mem_style malloc has failed");
	nbr = (int)map->num_players;
	if (!(map->players))
		error_call("Map->Players malloc has failed");
	while (--nbr >= 0)
	{
		map->players[nbr] = (t_bot *)NEW(t_bot);
		if (!(map->players[nbr]))
			error_call("Map->Players malloc has faildedsfdsf");
	}
}

t_cw_map		init_map(unsigned int n)
{
	t_cw_map	map;

	map = (t_cw_map){
		.memory = (unsigned char *)NEW_S(unsigned char, MEM_SIZE + 1),
		.mem_style = (unsigned char *)NEW_S(unsigned char, MEM_SIZE + 1),
		.num_players = n,
		.num_bots_init = 0,
		.players = (t_bot **)NEW_S(t_bot *, n + 1),
		.process = NULL,
		.suspended_proc = NULL,
		.lives_count = 0,
		.proc_count = 0,
		.cur_cycle = 0,
		.cycle_to_die = CYCLE_TO_DIE,
		.next_check = CYCLE_TO_DIE,
		.checks_perf = 0,
		.error_msg = NULL,
		.dump_cycle = -1,
		.f_disp = 0,
		.is_paused = 1,
		.cps = 50
	};
	check_malloc(&map);
	return (map);
}
