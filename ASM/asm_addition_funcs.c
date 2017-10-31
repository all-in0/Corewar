/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_addition_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:56:55 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/24 22:13:00 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label	*search_label(t_asm *as, char *str)
{
	t_label	*st;

	st = as->label;
	while (st && st->label)
	{
		if (ft_strcmp(st->label, str) == 0)
			return (st);
		st = st->next;
	}
	return (0);
}

char	*remove_comment_in_end(t_asm *as, char *s)
{
	char	*p;

	as->malloc_s = 0;
	if ((p = ft_strchr(s, COMMENT_CHAR)) > 0)
	{
		s = ft_strsub(s, 0, p - s);
		as->malloc_s = 1;
	}
	return (s);
}

char	*asm_trim(char *str)
{
	int	i;

	i = 0;
	while (*str && TAB(str[i]))
		i++;
	return (str + i);
}

int		index_list(t_asm *as)
{
	int		i;
	t_file	*s;

	i = 0;
	s = as->file;
	while (s)
	{
		s->row = ++i;
		s = s->next;
	}
	return (i);
}

void	asm_validate_end_str(char *str, t_file *st)
{
	if (str[0])
	{
		str = asm_trim(str);
		if (str[0] == COMMENT_CHAR || str[0] == '\0')
			return ;
		else
			asm_error("Lexical error", st, 0);
	}
}
