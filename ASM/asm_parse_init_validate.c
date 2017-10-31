/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_init_validate.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 21:24:58 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/16 20:24:28 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_struct(t_asm *as)
{
	as->data = (unsigned char *)malloc(sizeof(unsigned char) * SIZE);
	ft_bzero(as->data, sizeof(unsigned char) * SIZE);
	as->header = (t_header *)malloc(sizeof(t_header));
	as->header->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(as->header->prog_name, sizeof(char) * PROG_NAME_LENGTH + 1);
	as->header->prog_size = 0;
	ft_bzero(as->header->comment, sizeof(char) * COMMENT_LENGTH + 1);
	as->file = (t_file *)malloc(sizeof(t_file));
	*as->file = (t_file) {NULL, 0, NULL};
	as->label = (t_label *)malloc(sizeof(t_label));
	*as->label = (t_label) {NULL, 0, NULL};
	as->variable = (t_variable *)malloc(sizeof(t_variable));
	*as->variable = (t_variable) {NULL, 0, 0, 0, NULL};
}

void	asm_parse_name_comm_additional(char *s, t_asm *as, int flag)
{
	if (flag == 2)
	{
		if (ft_strlen(as->header->comment) + ft_strlen(s) + 1 <= COMMENT_LENGTH)
		{
			ft_strcat(as->header->comment, s);
			ft_strcat(as->header->comment, "\n");
		}
		else
			asm_error("Champion comment too long (Max length 2048)", 0, as);
	}
	else if (flag == 1)
	{
		if ((ft_strlen(as->header->prog_name) + ft_strlen(s) + 1)
			<= PROG_NAME_LENGTH)
		{
			ft_strcat(as->header->prog_name, s);
			ft_strcat(as->header->prog_name, "\n");
		}
		else
			asm_error("Champion name too long (Max length 128)", 0, as);
	}
}

void	asm_validate_coma(char *s, t_asm *as, t_file *st, int index)
{
	int	n;
	int	i;

	n = 0;
	i = -1;
	while (s[++i])
		if (s[i] == SEPARATOR_CHAR)
			n++;
	if (ft_strstr(s, ",,") > 0 ||
		(g_op_tab[index].count_arg == 1 && ft_strchr(s, ',')) ||
		(g_op_tab[index].count_arg == 2 && n != 1) ||
		(g_op_tab[index].count_arg == 3 && n != 2))
		asm_error("Syntax error SEPARATOR_CHAR", st, as);
}

int		asm_work_with_split(t_asm *as, char *s)
{
	int	i;

	i = -1;
	while (as->split && as->split[++i])
		ft_strdel(&as->split[i]);
	if (as->split)
	{
		free(as->split);
		as->split = NULL;
	}
	(!as->error) ? as->split = ft_strsplit(s, ',') : 0;
	i = -1;
	while (!as->error && as->split[++i])
		;
	return (i);
}

void	asm_validate_label_char(char *s, t_asm *as, t_file *st)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_strchr(LABEL_CHARS, s[i]) > 0)
			continue;
		else
			asm_error("Lexical error", st, as);
	}
}
