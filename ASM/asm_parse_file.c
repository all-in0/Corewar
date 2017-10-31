/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 21:26:28 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/24 22:38:42 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_file	*asm_parse_name_2(char *s, t_file *st, t_asm *as)
{
	char	*p;

	while (!as->error && st && as->flag_name != 1)
	{
		if ((p = ft_strchr(s, '\"')) > 0)
		{
			as->flag_name = 1;
			if ((ft_strlen(as->header->prog_name) + p - s) <= PROG_NAME_LENGTH)
			{
				ft_strncat(as->header->prog_name, s, p - s);
				asm_validate_end_str(p + 1, st);
			}
			else
				asm_error("Champion name too long (Max length 128)", 0, as);
		}
		else if (s[0] != '\0' && ft_strchr(s, '\"') == 0)
			asm_parse_name_comm_additional(s, as, 1);
		else if (!*s)
			ft_strcat(as->header->prog_name, "\n");
		(!as->error && as->flag_name != 1) ? st = st->next : 0;
		(!as->error && st) ? s = st->str : 0;
	}
	return (st);
}

t_file	*asm_parse_name(char *s, t_file *st, t_asm *as)
{
	if (s[0] == '\"' && s++)
	{
		if (s[0] == '\"' && (as->flag_name = 1))
		{
			asm_validate_end_str(s + 1, st);
			ft_strcpy(as->header->prog_name, "Default_name");
			return (st);
		}
		st = asm_parse_name_2(s, st, as);
		if (!as->error && as->flag_name != 1)
			asm_error("No .name", st, as);
	}
	else
		asm_error("Lexical error", st, as);
	return (st);
}

t_file	*asm_parse_comm_2(char *s, t_file *st, t_asm *as)
{
	char	*p;

	while (!as->error && st && as->flag_comm != 1)
	{
		if ((p = ft_strchr(s, '\"')) > 0)
		{
			as->flag_comm = 1;
			if ((ft_strlen(as->header->comment) + p - s) <= COMMENT_LENGTH)
			{
				ft_strncat(as->header->comment, s, p - s);
				asm_validate_end_str(p + 1, st);
			}
			else
				asm_error("Champion comment too long (Max length 2048)", 0, as);
		}
		else if (s[0] != '\0' && ft_strchr(s, '\"') == 0)
			asm_parse_name_comm_additional(s, as, 2);
		else if (!*s)
			ft_strcat(as->header->comment, "\n");
		(!as->error && as->flag_comm != 1) ? st = st->next : 0;
		(!as->error && st) ? s = st->str : 0;
	}
	return (st);
}

t_file	*asm_parse_comm(char *s, t_file *st, t_asm *as)
{
	if (s[0] == '\"' && s++)
	{
		if (s[0] == '\"' && (as->flag_comm = 1))
		{
			asm_validate_end_str(s + 1, st);
			ft_strcpy(as->header->comment, "Default_comment");
			return (st);
		}
		st = asm_parse_comm_2(s, st, as);
		if (!as->error && as->flag_comm != 1)
			asm_error("No .comment", st, as);
	}
	else
		asm_error("Lexical error", st, as);
	return (st);
}

void	asm_parse_name_comm(t_asm *as)
{
	t_file	*st;
	char	*s;

	st = as->file;
	while (st && !as->error && (s = asm_trim(st->str)) && (as->flag_name != 1 ||
		as->flag_comm != 1))
	{
		if (s[0] != '\0' && s[0] != '#')
		{
			if (ft_strncmp(s, NAME_CMD_STRING,
			ft_strlen(NAME_CMD_STRING)) == 0 && ft_strchr(s, '\"') > 0)
				st = asm_parse_name(asm_trim(s + 5), st, as);
			else if (ft_strncmp(s, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING)) == 0 && ft_strchr(st->str, '\"') > 0)
				st = asm_parse_comm(asm_trim(s + 8), st, as);
			else
				asm_error("Syntax error", st, as);
		}
		st = st->next;
	}
	if (!as->error && as->flag_name == 1 && as->flag_comm == 1)
		asm_parse_program(s, st, as);
	else if (!as->error && !as->flag_name && !as->flag_comm)
		asm_error("No name or comment", 0, as);
}
