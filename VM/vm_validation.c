/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:11:15 by vnakonec          #+#    #+#             */
/*   Updated: 2017/10/28 11:12:50 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			error_call(char *msg)
{
	ft_putstr_fd("Error. ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(".\n", 2);
	exit(2);
}

void			check_bot_number(int bot_i, int *bot_nbr, int (*bot_tab)[4])
{
	int			i;

	i = -1;
	while (++i < bot_i)
	{
		if ((*bot_tab)[i] == (*bot_nbr))
		{
			(*bot_nbr) = (*bot_nbr < 0) ? (*bot_nbr) - 1 : (*bot_nbr) + 1;
			check_bot_number(bot_i, bot_nbr, bot_tab);
		}
	}
}
