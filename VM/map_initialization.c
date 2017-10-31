/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:09:51 by vnakonec          #+#    #+#             */
/*   Updated: 2017/10/28 11:18:02 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_set_map_style(unsigned char *styles, t_bot *bot, int offset)
{
	int		id;
	int		size;

	id = bot->id;
	size = (int)bot->header->prog_size;
	while (--size >= 0)
		styles[offset + size] = (unsigned char)id;
}

int			is_cmd_flag(char *str)
{
	if (__builtin_strcmp(str, "-n") == 0 ||
		__builtin_strcmp(str, "-dump") == 0)
		return (2);
	if (__builtin_strcmp(str, "-v") == 0)
		return (1);
	return (0);
}

int			ft_isnumeric(char *str, int is_neg_allowed)
{
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\t')
		str++;
	if (is_neg_allowed && *str == '-')
		str++;
	while (*str)
	{
		if ((*str) < '0' || (*str) > '9')
			return (0);
		str++;
	}
	return (1);
}

t_byte		cw_parse_flags(t_cw_map *map, char **av, int (*data)[4])
{
	int		d_cycle;

	if (__builtin_strcmp(av[(*data)[0]], "-dump") == 0 && (++(*data)[0]))
	{
		d_cycle = ft_atoi(av[(*data)[0]]);
		if (d_cycle <= 0 || !ft_isnumeric(av[(*data)[0]], 0))
			map->error_msg = "Dump cycle must be a number greater than 0";
		else
			map->dump_cycle = d_cycle;
	}
	else if (__builtin_strcmp(av[(*data)[0]], "-n") == 0 && (++(*data)[0]))
	{
		(*data)[3] = 1;
		if (((*data)[2] = ft_atoi(av[(*data)[0]])) == 0 ||
			!ft_isnumeric(av[*(data)[0]], 1))
			map->error_msg = "Bot number can't be zero or blank";
	}
	else if (__builtin_strcmp(av[(*data)[0]], "-v") == 0)
		map->f_disp = 1;
	return (1);
}

void		fill_map_data(t_cw_map *map, int ac, char **av)
{
	int		int_data[4];
	char	bot_i;
	int		bot_nums[4];

	bot_i = 0;
	int_data[3] = 0;
	int_data[1] = -1;
	int_data[0] = 0;
	while (++int_data[0] < ac && !(map->error_msg))
	{
		if (is_cmd_flag(av[int_data[0]]))
			cw_parse_flags(map, av, &int_data);
		else
		{
			if (!int_data[3])
				int_data[2] = int_data[1]--;
			check_bot_number(bot_i, &int_data[2], &bot_nums);
			bot_nums[(int)bot_i] = int_data[2];
			save_bot(map, int_data[2], bot_i, av[int_data[0]]);
			bot_i++;
			int_data[3] = 0;
		}
	}
}
