/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:29:36 by vnakonec          #+#    #+#             */
/*   Updated: 2017/10/28 04:29:40 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_byte			cw_draw_info(t_cw_map *map)
{
	int		pass_lines;

	attron(COLOR_PAIR(0));
	(map->is_paused) ? mvprintw(2, 221, "...PAUSE...") :
		mvprintw(2, 221, "...RUNNING...");
	mvprintw(6, 200, "Cycle : %9i", map->cur_cycle);
	mvprintw(8, 200, "CPS   : %9i", map->cps);
	pass_lines = map->num_players * 3 + 2;
	mvprintw(10, 200, "Total process : %10i", map->proc_count);
	cw_put_bot_stat(map->players, map->num_players);
	mvprintw(15 + pass_lines, 201, "CYCLE_TO_DIE : %10i", map->cycle_to_die);
	mvprintw(17 + pass_lines, 201, "NEXT_CHECK   : %10i", map->next_check);
	mvprintw(19 + pass_lines, 201, "CYCLE_DELTA  : %10i", CYCLE_DELTA);
	mvprintw(21 + pass_lines, 201, "NBR_LIVE     : %10i", NBR_LIVE);
	mvprintw(23 + pass_lines, 201, "MAX_CHECKS   : %10i", MAX_CHECKS);
	mvprintw(23 + pass_lines, 231, "( check : %2i )", map->checks_perf);
	attroff(COLOR_PAIR(0));
	return (1);
}

t_byte			cw_draw_mem(t_cw_map *map)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != MEM_SIZE - 1)
			j++;
		attron(COLOR_PAIR(map->mem_style[i]));
		mvprintw(j + 1, (i % 64) * 3 + 3, "%02x", (t_byte)map->memory[i]);
		attroff(COLOR_PAIR(map->mem_style[i]));
	}
	return (1);
}

t_byte			cw_draw_line(int fixed, int i_max, char direction)
{
	int		i;

	i = -1;
	if (direction == 'h')
	{
		while (++i < i_max)
			mvprintw(fixed, i, "z");
		return (1);
	}
	else if (direction == 'v')
	{
		while (++i < i_max)
			mvprintw(i, fixed, "z");
		return (1);
	}
	return (0);
}

void			cw_scr_redraw(t_cw_map *map)
{
	attron(COLOR_PAIR(PAIR_WW));
	DL(0, 255, 'h') && DL(67, 255, 'h') &&
		DL(0, 68, 'v') && DL(196, 68, 'v') && DL(254, 68, 'v');
	attroff(COLOR_PAIR(PAIR_WW));
	cw_put_proc_style(map->mem_style, map->process);
	cw_draw_mem(map) && cw_draw_info(map);
	refresh();
}

void			cw_visualizer(t_cw_map *map)
{
	initscr();
	cbreak();
	curs_set(0);
	noecho();
	nodelay(stdscr, TRUE);
	if (can_change_color() == true)
	{
		start_color();
		init_color(COLOR_WHITE, 505, 405, 305);
		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(100, COLOR_BLACK, COLOR_WHITE);
		init_pair(PAIR_WW, COLOR_WHITE, COLOR_WHITE);
		init_bot_colors(map->num_players);
	}
	cw_put_proc_style(map->mem_style, map->process);
	cw_scr_redraw(map);
	cw_run_fight_v(map);
	endwin();
	curs_set(1);
}
