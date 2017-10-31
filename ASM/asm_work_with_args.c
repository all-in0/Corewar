/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_work_with_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 21:17:45 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/16 20:23:26 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_t_dir(t_asm *as, t_file *st, char *s, int index)
{
	unsigned	n;

	n = 0;
	if (s[0] == ':')
	{
		if (ft_strchr(LABEL_CHARS, s[1]) > 0)
			n = (unsigned)asm_variable(as, s + 1, g_op_tab[index].t_dir_size);
		else
			asm_error("Lexical error", st, as);
	}
	else
		n = (unsigned)asm_atoi(s, st, as);
	(!as->error) ? asm_coding_arg(as, n, g_op_tab[index].t_dir_size) : 0;
}

void	asm_t_reg(t_asm *as, t_file *st, char *s)
{
	int	n;

	n = 0;
	if (!(s[0] >= '0' && s[0] <= '9'))
		asm_error("Invalid parameter", st, as);
	n = asm_atoi(s, st, as);
	if (n < 0 || n > 99)
		asm_error("T_REG must be from 1 to REG_SIZE", st, as);
	(!as->error) ? asm_coding_arg(as, n, 1) : 0;
}

void	asm_t_ind(t_asm *as, t_file *st, char *s)
{
	unsigned	n;

	n = 0;
	if (s[0] == ':')
	{
		if (ft_strchr(LABEL_CHARS, s[1]) > 0)
			n = (unsigned)asm_variable(as, s + 1, 2);
		else
			asm_error("Lexical error", st, as);
	}
	else
		n = (unsigned)asm_atoi(s, st, as);
	asm_coding_arg(as, n, 2);
}

/*
** парсить аргументи в строці
*/

void	asm_parse_arg(t_file *st, t_asm *as, int index)
{
	int		i;
	char	*s;

	i = -1;
	while (as->split[++i] && !as->error && (s = asm_trim(as->split[i])))
	{
		if (s[0] == DIRECT_CHAR)
		{
			if ((g_op_tab[index].arg[i] & T_DIR) != T_DIR)
				asm_error("Invalid parameter", st, as);
			(!as->error) ? asm_t_dir(as, st, s + 1, index) : 0;
		}
		else if (s[0] == 'r')
		{
			if ((g_op_tab[index].arg[i] & T_REG) != T_REG)
				asm_error("Invalid parameter", st, as);
			(!as->error) ? asm_t_reg(as, st, s + 1) : 0;
		}
		else
		{
			if ((g_op_tab[index].arg[i] & T_IND) != T_IND)
				asm_error("Invalid parameter", st, as);
			(!as->error) ? asm_t_ind(as, st, s) : 0;
		}
	}
}

/*
** записує в масив типи аргументів iнструкції
*/

void	asm_arg(t_asm *as)
{
	int		i;
	char	*s;

	i = -1;
	while (as->split[++i] && i < 3)
	{
		s = asm_trim(as->split[i]);
		if (s[0] == DIRECT_CHAR)
			as->arg[i] = DIR_CODE;
		else if (s[0] == LABEL_CHAR ||
			(s[0] >= '0' && s[0] <= '9') || s[0] <= '-')
			as->arg[i] = IND_CODE;
		else if (s[0] == 'r')
			as->arg[i] = REG_CODE;
	}
}
