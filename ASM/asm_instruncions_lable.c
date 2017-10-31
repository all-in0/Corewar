/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_instruncions_label.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 21:26:30 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/16 20:27:53 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_save_label(t_asm *as, t_file *st, char *s, int l)
{
	t_label	*st_label;
	char	*str;

	str = ft_strsub(s, 0, l);
	st_label = as->label;
	while (st_label && st_label->label != NULL)
	{
		if (st_label->label != NULL && !ft_strcmp(st_label->label, str))
			return ;
		if (st_label->next == NULL)
		{
			st_label->next = (t_label *)malloc(sizeof(t_label));
			*st_label->next = (t_label) {NULL, 0, NULL};
		}
		st_label = st_label->next;
	}
	st_label->label = ft_strdup(str);
	st_label->byte = as->i;
	free(str);
	asm_validate_label_char(st_label->label, as, st);
}

/*
** зберігає лейбл як змінну в яку записати значення
*/

void	asm_save_variable(t_asm *as, char *s, int size_byte)
{
	t_variable *st_var;

	st_var = as->variable;
	while (st_var && st_var->variable != NULL)
	{
		if (st_var->next == NULL)
		{
			st_var->next = (t_variable *)malloc(sizeof(t_variable));
			*st_var->next = (t_variable) {NULL, 0, 0, 0, NULL};
		}
		st_var = st_var->next;
	}
	st_var->variable = ft_strdup(s);
	st_var->current_byte = as->i;
	st_var->start_byte = as->st_byte;
	st_var->size_arg = size_byte;
}

/*
** шукає лейбл в списку якщо є записує як аргумент якщо ні зберігає в
** список змінниї
*/

int		asm_variable(t_asm *as, char *s, int size_byte)
{
	t_label		*st_label;
	char		*str;

	str = ft_strtrim(s);
	st_label = as->label;
	while (st_label && st_label->label)
	{
		if (ft_strcmp(st_label->label, str) == 0)
		{
			free(str);
			return (st_label->byte - as->st_byte);
		}
		st_label = st_label->next;
	}
	asm_save_variable(as, str, size_byte);
	free(str);
	return (0);
}

void	asm_parse_instruction(char *s, t_file *st, t_asm *as)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (s[0] == '#')
		return ;
	while (g_op_tab[++i].name)
	{
		len = ft_strlen(g_op_tab[i].name);
		if (ft_strncmp(s, g_op_tab[i].name, len) == 0 && (TAB(s[len]) ||
			s[len] == DIRECT_CHAR))
		{
			s = asm_trim(s + len);
			asm_instruction(s, st, as, i);
			return ;
		}
	}
	asm_error("Invalid instruction", st, as);
}

/*
** перевіряє і сплітить строку з інструкцією
*/

void	asm_instruction(char *s, t_file *st, t_asm *as, int index)
{
	int		count_arg;
	int		n;

	if (as->i + 15 >= SIZE && st->next)
		asm_error("File is too large!", 0, as);
	as->st_byte = as->i;
	(!as->error) ? asm_coding_arg(as, (unsigned)g_op_tab[index].op_code, 1) : 0;
	(!as->error) ? s = remove_comment_in_end(as, s) : 0;
	(!as->error) ? asm_validate_coma(s, as, st, index) : 0;
	count_arg = asm_work_with_split(as, s);
	if (!as->error && count_arg != g_op_tab[index].count_arg)
		asm_error("Invalid parameters for instruction", st, as);
	if (!as->error && g_op_tab[index].codage == 1)
	{
		n = asm_coding_number_arg(as, index);
		asm_coding_arg(as, (unsigned)n, 1);
	}
	(!as->error) ? asm_parse_arg(st, as, index) : 0;
	(as->malloc_s) ? free(s) : 0;
}
