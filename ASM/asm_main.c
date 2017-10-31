/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 21:40:13 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/24 22:10:15 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_parse_program(char *s, t_file *st, t_asm *as)
{
	char	*p;

	while (!as->error && st && st->str && !as->error)
	{
		s = (*st->str && TAB(st->str[0])) ? asm_trim(st->str) : st->str;
		if (s[0] == COMMENT_CHAR || s[0] == '\0')
			;
		else if ((p = ft_strchr(s, LABEL_CHAR)) > 0 &&
			s[(p - s) - 1] != SEPARATOR_CHAR &&
			s[(p - s) - 1] != DIRECT_CHAR && !TAB(s[(p - s) - 1]))
		{
			asm_save_label(as, st, s, (int)(p - s));
			s = asm_trim(s + (p - s) + 1);
			(*s) ? asm_parse_instruction(s, st, as) : 0;
		}
		else if ((ft_strnstr(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) > 0
			|| ft_strnstr(s, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING)) > 0) && as->data[0])
			break ;
		else if (*s && !as->error)
			asm_parse_instruction(s, st, as);
		st = st->next;
	}
}

void	asm_check_file(t_asm *as, int fd, int check)
{
	if (fd < 0 || check < 0)
		asm_error("File is empty or no file", 0, as);
	(!as->error) ? asm_lseek(fd, as) : 0;
	(!as->error) ? as->count_rows = index_list(as) : 0;
	(!as->error) ? asm_parse_name_comm(as) : 0;
	(!as->error) ? as->header->prog_size = as->i : 0;
	(!as->error) ? asm_rewrite_variable_in_data(as) : 0;
	(!as->error) ? asm_write_in_file(as) : 0;
}

void	asm_read_file(char *av, t_asm *as)
{
	char	*line;
	int		fd;
	int		check;
	t_file	*st;

	st = as->file;
	fd = open(av, O_RDONLY);
	line = NULL;
	while (fd > 0 && (check = get_next_line(fd, &line)) > 0)
	{
		if (st->str == NULL)
			st->str = ft_strdup(line);
		else if (st->str != NULL)
		{
			st->next = (t_file *)malloc(sizeof(t_file));
			*st->next = (t_file) {NULL, 0, NULL};
			st = st->next;
			st->str = ft_strdup(line);
		}
		free(line);
	}
	line ? free(line) : 0;
	asm_check_file(as, fd, check);
}

void	check_name(char *av)
{
	t_asm	as;
	int		len;
	char	*tmp;
	char	*cor;

	as = (t_asm){NULL, NULL, 0, 0, 0, NULL, {0, 0, 0},
				0, 0, 0, 0, NULL, NULL, NULL, NULL};
	len = (int)ft_strlen(av);
	if (len <= 2 || (av[len - 1] != 's' && av[len - 2] != '.'))
	{
		asm_error("Wrong name file .s", 0, 0);
		return ;
	}
	as.name_cor = ft_strsub(av, 0, len - 1);
	cor = ft_strdup("cor");
	tmp = as.name_cor;
	as.name_cor = ft_strjoin(tmp, cor);
	free(tmp);
	free(cor);
	init_struct(&as);
	asm_read_file(av, &as);
	asm_free_struct(&as);
}

int		main(int ac, char **av)
{
	int i;

	i = 0;
	if (ac <= 1)
		asm_error("You need to enter filename. Use: ./asm name.s", 0, 0);
	while (--ac && ++i)
		check_name(av[i]);
	return (0);
}
