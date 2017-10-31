/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 00:52:08 by vnakonec          #+#    #+#             */
/*   Updated: 2017/10/28 12:16:38 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op		g_op_tab[] = {
	{"live", 1, {T_DIR}, 1, 10, "", 0, 0, 1},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "", 1, 1, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "", 1, 0, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "", 1, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "", 1, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, "", 1, 1, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, "", 1, 1, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, "", 1, 1, 1},
	{"zjmp", 1, {T_DIR}, 9, 20, "", 0, 0, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		10, 25, "", 1, 0, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		11, 25, "", 1, 0, 0},
	{"fork", 1, {T_DIR}, 12, 800, "", 0, 0, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "", 1, 1, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, "", 1, 1, 0},
	{"lfork", 1, {T_DIR}, 15, 1000, "", 0, 0, 0},
	{"aff", 1, {T_REG}, 16, 2, "", 1, 0, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
};

t_byte		cw_run_fight(t_cw_map *map)
{
	while (map->process)
	{
		cw_execute_process(map);
		if (map->next_check <= map->cur_cycle)
			cw_check_lives(map);
		if (map->dump_cycle != -1 && map->cur_cycle >= map->dump_cycle)
			cw_show_dump(map);
		map->cur_cycle++;
	}
	cw_vm_stop(map);
	return (1);
}

t_byte		cw_run_fight_v(t_cw_map *map)
{
	t_byte		control_char;

	control_char = 0;
	while (control_char != 27)
	{
		if ((control_char = getch()) == 32)
			map->is_paused = map->is_paused ? 0 : 1;
		cw_adjust_cps(control_char, &(map->cps));
		if (!(map->is_paused) || (map->is_paused && control_char == 115))
		{
			cw_execute_process(map);
			if (map->next_check <= map->cur_cycle)
				cw_check_lives(map);
			if (map->dump_cycle != -1 && map->cur_cycle >= map->dump_cycle)
				cw_show_dump(map);
			cw_scr_redraw(map);
			map->cur_cycle++;
			usleep(1000000 / map->cps);
		}
		else if (map->is_paused && map->f_disp)
			cw_draw_info(map);
		cw_degug_show_key(control_char);
	}
	endwin();
	return (1);
}

static int	get_num_bots(int ac, char **av)
{
	int				i;
	unsigned int	num_bots;
	int				f_size;

	num_bots = ac - 1;
	i = 0;
	if (ac == 1)
	{
		ft_printf("Usage: ./corewar [-v][-n number][-dump number] file.cor.\n");
		ft_printf("\t %-10s - encurses output\n", "-v");
		ft_printf("\t %-10s - set bot number\n", "-n");
		ft_printf("\t %-10s - set dump cycle\n", "-dump");
		exit(1);
	}
	while (++i < ac)
	{
		if (av[i][0] == '-' && (f_size = is_cmd_flag(av[i])))
		{
			if (i == ac - 1 || is_cmd_flag(av[i + 1]))
				num_bots -= 1;
			else
				num_bots -= f_size;
		}
	}
	return (num_bots);
}

int			main1(int ac, char **av)
{
	unsigned int	num_bot_args;
	t_cw_map		map;

	num_bot_args = get_num_bots(ac, av);
	if (num_bot_args > 4)
		error_call("Too many champions");
	else if (num_bot_args > 0)
	{
		map = init_map(num_bot_args);
		fill_map_data(&map, ac, av);
		if (map.error_msg)
		{
			error_call(map.error_msg);
			free_map(&map);
		}
		if (map.f_disp)
			cw_visualizer(&map);
		else
			print_bots_stats(&map) && cw_run_fight(&map);
		free_map(&map);
	}
	else
		error_call("No champion files");
	return (1);
}

int			main(int ac, char **av)
{
	main1(ac, av);
}
