/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:14:47 by vnakonec          #+#    #+#             */
/*   Updated: 2017/10/28 05:40:23 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*pop_top_process(t_process **list)
{
	t_process	*ps;

	if ((*list) == NULL)
		return (NULL);
	ps = (*list);
	(*list) = (*list)->next;
	ps->next = NULL;
	return (ps);
}

t_process		*pop_process(t_process **prev_el)
{
	t_process	*ps;

	ps = (*prev_el)->next;
	(*prev_el)->next = (*prev_el)->next->next;
	ps->next = NULL;
	return (ps);
}

void			push_process(t_process **list, t_process *n)
{
	if ((*list) == NULL)
		(*list) = n;
	else
	{
		n->next = (*list);
		(*list) = n;
	}
}
