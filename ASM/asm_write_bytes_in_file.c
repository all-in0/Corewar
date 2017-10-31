/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_bytes_in_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 21:17:47 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/24 22:10:57 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_write_magic_prog_size(int fd, unsigned value)
{
	unsigned char temp;

	temp = value >> 24;
	write(fd, &temp, 1);
	temp = value >> 16;
	write(fd, &temp, 1);
	temp = value >> 8;
	write(fd, &temp, 1);
	temp = value;
	write(fd, &temp, 1);
}

void	asm_write_in_file(t_asm *as)
{
	int	fd;
	int	i;

	i = -1;
	if ((fd = open(as->name_cor, O_TRUNC | O_WRONLY | O_APPEND |
		O_CREAT, S_IROTH | S_IRUSR | S_IWUSR)) < 0)
	{
		asm_error("Error! Can't create .cor file", 0, as);
		return ;
	}
	asm_write_magic_prog_size(fd, as->header->magic);
	write(fd, &as->header->prog_name, PROG_NAME_LENGTH + 1);
	write(fd, "\0\0\0", 3);
	asm_write_magic_prog_size(fd, as->header->prog_size);
	write(fd, &as->header->comment, COMMENT_LENGTH + 1);
	write(fd, "\0\0\0", 3);
	while (++i < (int)as->header->prog_size)
		write(fd, &as->data[i], 1);
	write(1, GRN, ft_strlen(GRN));
	write(1, "Writing output program to ", 26);
	write(1, as->name_cor, ft_strlen(as->name_cor));
	write(1, RESET, ft_strlen(RESET));
	write(1, "\n", 1);
}

void	asm_coding_arg(t_asm *as, unsigned value, int n)
{
	unsigned char	temp;

	if (n == 4 && !as->error)
	{
		temp = (value >> (8 * 3)) & 0xFF;
		as->data[as->i++] = temp;
		temp = (value >> (8 * 2)) & 0xFF;
		as->data[as->i++] = temp;
		temp = (value >> (8 * 1)) & 0xFF;
		as->data[as->i++] = temp;
		temp = value & 0xFF;
		as->data[as->i++] = temp;
	}
	else if (n == 2 && !as->error)
	{
		temp = (value >> (8 * 1)) & 0xFF;
		as->data[as->i++] = temp;
		temp = value & 0xFF;
		as->data[as->i++] = temp;
	}
	else if (n == 1 && !as->error)
	{
		temp = value;
		as->data[as->i++] = temp;
	}
}

/*
** закодовує аргументи в кодуючий байт
*/

int		asm_coding_number_arg(t_asm *as, int index)
{
	int	n;
	int	i;

	as->arg[0] = 0;
	as->arg[1] = 0;
	as->arg[2] = 0;
	n = 0;
	i = -1;
	asm_arg(as);
	while (as->arg[++i] != 0 && i < 3)
	{
		n = (n | as->arg[i]);
		if (g_op_tab[index].count_arg == 1)
			n = n << 6;
		else if (i == 1 && g_op_tab[index].count_arg == 2)
			n = n << 4;
		else
			n = n << 2;
	}
	return (n);
}

/*
** перезаписує пропущені місця в data (якщо лейбл зустріли знизу)
*/

void	asm_rewrite_variable_in_data(t_asm *as)
{
	t_variable	*st_var;
	t_label		*label;

	st_var = as->variable;
	while (!as->error && st_var && st_var->variable)
	{
		if ((label = search_label(as, st_var->variable)) > 0)
		{
			as->i = st_var->current_byte;
			asm_coding_arg(as, (unsigned)(label->byte - st_var->start_byte),
				st_var->size_arg);
		}
		else
		{
			write(1, "No such label - ", 16);
			asm_error(st_var->variable, 0, as);
			return ;
		}
		st_var = st_var->next;
	}
}
