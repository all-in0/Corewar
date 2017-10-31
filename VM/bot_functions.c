/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:24:31 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 10:50:20 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_byte		check_file_fd(int fd)
{
	if (fd <= 0)
		exit(write(1, "Empty file/ Doesn't exist\n", 26));
	return (1);
}

t_byte		check_filename_ext(const char *filename)
{
	char *dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	return (!ft_strcmp(&dot[1], "cor") ? 1 : 0);
}

t_header	*parse_bot_header(t_cw_map *map, char *f_name, int fd)
{
	int			bytes_read;
	t_header	*h;

	h = NEW(t_header);
	if ((bytes_read = read(fd, h, 2192)) != 2192)
		map->error_msg = ft_strjoin(f_name,
			" is to small to be a champion");
	reverse_bytes((int *)&(h->prog_size), 4);
	if (h->prog_size > CHAMP_MAX_SIZE)
		map->error_msg = ft_strjoin(f_name, " is to big to be a champion");
	else if (h->prog_size == 0)
		map->error_msg = ft_strjoin(f_name, " has no code");
	reverse_bytes((int *)&(h->magic), 4);
	return (h);
}

void		save_bot(t_cw_map *map, int bot_nbr, int bot_i, char *f_name)
{
	int			fd;
	t_header	*head;
	int			bot_offset;

	if (!check_filename_ext(f_name))
		exit(write(1, "Wrong filename extension, use .cor file\n", 40));
	bot_offset = MEM_SIZE / map->num_players * bot_i;
	if (map && bot_i < map->num_players)
	{
		check_file_fd(fd = open(f_name, O_RDONLY));
		head = parse_bot_header(map, f_name, fd);
		map->players[bot_i]->id = bot_i + 1;
		map->players[bot_i]->header = (t_header *)head;
		map->players[bot_i]->name = bot_nbr;
		cw_set_reg_rev(&(map->players[bot_i]->reg[0]), bot_nbr);
		if (head->magic != 0xea83f3)
			map->error_msg = ft_strjoin(f_name, " not valid .cor file");
		if (read(fd, map->memory + bot_offset,
			head->prog_size + 1) != head->prog_size)
			map->error_msg = ft_strjoin(f_name, " file is corrupted");
		map->num_bots_init = bot_i + 1;
		cw_set_map_style(map->mem_style, map->players[bot_i], bot_offset);
		close(fd);
	}
	create_process(map, NULL, bot_i, bot_offset);
}
