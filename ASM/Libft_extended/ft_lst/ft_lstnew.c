/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 19:20:06 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 19:59:27 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;
	char	*str;

	if ((list = (t_list *)malloc(sizeof(t_list))))
	{
		if (!content)
		{
			content_size = 0;
			str = NULL;
		}
		else
		{
			str = malloc(content_size);
			str = ft_strncpy(str, content, content_size);
		}
		list->content_size = content_size;
		list->content = str;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}
