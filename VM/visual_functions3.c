/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 04:30:27 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 10:12:39 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_byte			print_bots_stats(t_cw_map *map)
{
	int			i;
	int			num_bots;
	static char *w = "weighting\0";

	i = -1;
	num_bots = map->num_players;
	while (++i < num_bots)
	{
		ft_printf("* Player %i, %s %u bytes, \"%s\" (\"%s\")!\n",
			i + 1,
			w,
			map->players[i]->header->prog_size,
			map->players[i]->header->prog_name,
			map->players[i]->header->comment);
	}
	return (1);
}

void			cw_put_bot_stat(t_bot **bots, int num_p)
{
	int		i;

	i = -1;
	while (++i < num_p)
	{
		mvprintw(12 + i * 3, 201, "Player %5i : ", bots[i]->name);
		attron(COLOR_PAIR(i + 1));
		mvprintw(12 + i * 3, 217, bots[i]->header->prog_name);
		attroff(COLOR_PAIR(i + 1));
		mvprintw(13 + i * 3, 206, "Last live : %19i", bots[i]->last_live_cycle);
		mvprintw(14 + i * 3, 206, "Lives in current period : %5i",
				bots[i]->lives_in_period);
	}
}

void			cw_disp_winner(char *name, int cycle, int bot_id, int nbr)
{
	t_byte	control_char;

	mvprintw(50, 208, "And the winner is player : %3i", nbr);
	attron(COLOR_PAIR(bot_id));
	mvprintw(52, 208, "%s", name);
	attroff(COLOR_PAIR(bot_id));
	mvprintw(54, 208, "Last lived on %i cycle", cycle);
	refresh();
	control_char = 0;
	while (1)
	{
		if ((control_char = getch()) == 27)
		{
			endwin();
			exit(curs_set(1));
		}
	}
}
