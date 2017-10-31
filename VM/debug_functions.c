/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:53:13 by vnakonec          #+#    #+#             */
/*   Updated: 2017/10/28 05:51:15 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op g_op_tab[];

void		cw_debug_msgbox_aff_clean(void)
{
	short	i;

	i = -1;
	while (++i < 6)
		mvprintw(60 + i, 215, "                ");
	refresh();
}

void		cw_debug_msgbox_aff(int value)
{
	static short	i = 0;
	static short	j = -1;
	t_byte			c;

	j++;
	if (j > 13)
	{
		i++;
		j = 0;
	}
	if (i > 2)
	{
		cw_debug_msgbox_aff_clean();
		i = 0;
		j = 0;
	}
	c = (t_byte)(value % 256);
	if (c >= 32 && c <= 126)
		mvprintw(60 + i, 215 + j, "%c", c);
	else
		mvprintw(60 + i, 215 + j, "*");
	refresh();
}

void		cw_debug_disp_regs(t_byte regs[REG_NUMBER][REG_SIZE], int bot_id)
{
	int			i;
	int			j;

	mvprintw(45, 187 + 13 * bot_id, "REGISTERS : ");
	i = -1;
	while (++i < REG_NUMBER)
	{
		j = -1;
		while (++j < REG_SIZE)
			mvprintw(45 + 1 + i, 187 + 13 * bot_id + (j * 3),
					"%02x", regs[i][j]);
	}
}

void		cw_degug_show_key(t_byte key)
{
	mvprintw(43, 211, "( keycode : %3hhu )", key);
}

void		debug_announce_bots(t_cw_map *map)
{
	int		i;
	t_bot	*cur_bot;

	i = -1;
	while (++i < map->num_players)
	{
		cur_bot = map->players[i];
		__builtin_printf("BOT number : %i, BOT name : %s\n",
				cur_bot->name, cur_bot->header->prog_name);
		__builtin_printf("BOT size : %u, BOT comment : %s\n",
				cur_bot->header->prog_size, cur_bot->header->comment);
	}
}
