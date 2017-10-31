/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 05:53:30 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 05:53:31 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_debug_msg_box(char *msg, int i)
{
	mvprintw(63, 225, "                           ");
	mvprintw(63, 225, "%s %i", msg, i);
	refresh();
}

void		cw_debug_msg_box_line(char *msg, int i, int line)
{
	mvprintw(50 + line, 225, "                           ");
	mvprintw(50 + line, 225, "%s %i", msg, i);
	refresh();
}
