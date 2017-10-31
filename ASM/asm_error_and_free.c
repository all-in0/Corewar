/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error_and_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 20:43:35 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/22 23:30:12 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_free_variable_label_file(t_variable *variable, t_label *label,
	t_file *file)
{
	t_variable	*vr;
	t_label		*lb;
	t_file		*fl;

	while (variable)
	{
		vr = variable;
		variable = variable->next;
		(vr && vr->variable) ? free(vr->variable) : 0;
		free(vr);
	}
	while (label)
	{
		lb = label;
		label = label->next;
		(lb && lb->label) ? free(lb->label) : 0;
		free(lb);
	}
	while (file)
	{
		fl = file;
		file = file->next;
		(fl->str) ? free(fl->str) : 0;
		free(fl);
	}
}

void	asm_free_struct(t_asm *as)
{
	int	i;

	i = -1;
	if (as)
	{
		(as && as->name_cor) ? free(as->name_cor) : 0;
		(as && as->data) ? free(as->data) : 0;
		if (as->split)
		{
			while (as->split && as->split[++i])
				(as->split[i]) ? free(as->split[i]) : 0;
			free(as->split);
		}
		if (as->header)
			free(as->header);
		asm_free_variable_label_file(as->variable, as->label, as->file);
	}
}

void	asm_error(char *s, t_file *st, t_asm *as)
{
	if (st == 0)
	{
		write(1, RED, ft_strlen(RED));
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		write(1, RESET, ft_strlen(RESET));
	}
	else
	{
		write(1, RED, ft_strlen(RED));
		write(1, s, ft_strlen(s));
		write(1, " at row - ", 10);
		ft_putnbr(st->row);
		write(1, RESET, ft_strlen(RESET));
		write(1, "\n", 1);
	}
	as ? as->error = 1 : 0;
}

void	asm_lseek(int fd, t_asm *as)
{
	char buf[1];

	lseek(fd, -1L, SEEK_END);
	read(fd, buf, 1);
	if (buf[0] != '\n')
		asm_error("Syntax error - you forgot to end with a newline?", 0, as);
}

int		asm_atoi(char *str, t_file *st, t_asm *as)
{
	int	s;
	int	numb;

	s = 1;
	numb = 0;
	if (*str == '-')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		numb = numb * 10 + (*str - '0');
		str++;
	}
	(!as->error) ? str = asm_trim(str) : 0;
	if (*str && *str != COMMENT_CHAR)
		asm_error("Invalid parameter", st, as);
	return (numb * s);
}
