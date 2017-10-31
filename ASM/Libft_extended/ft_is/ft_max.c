/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:21:10 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:59:38 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_max(int *ag, unsigned int len)
{
	int				max;
	unsigned int	i;

	i = 0;
	if (ag[0] == '\0')
		return (0);
	max = ag[0];
	while (i < len)
	{
		if (max < ag[i])
			max = ag[i];
		i++;
	}
	return (max);
}
