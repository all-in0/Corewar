/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 14:27:36 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 20:17:41 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_111(char **rest, int bts, char *buf)
{
	char *ptr;
	char *ptr2;

	ptr = *rest;
	if (bts < BUFF_SIZE)
	{
		ptr2 = ft_strsub(buf, 0, bts);
		*rest = ft_strjoin(*rest, ptr2);
		free(ptr2);
	}
	else
		*rest = ft_strjoin(*rest, buf);
	free(ptr);
	return (*rest);
}

char	*ft_initialize(char **rest, char **line, char *chr)
{
	*line = ft_strsub(*rest, 0, chr - *rest);
	return (*rest);
}

int		ft_read_write(int fd, char **rest, char **line)
{
	t_vault		s;

	ft_bzero(s.buf, BUFF_SIZE + 1);
	while ((!(s.chr = ft_strchr(*rest, '\n'))) > 0)
		if ((s.bts = read(fd, s.buf, BUFF_SIZE)) > 0)
			*rest = ft_111(rest, s.bts, s.buf);
		else if (s.bts == 0)
		{
			*line = ft_strdup(*rest);
			free(*rest);
			*rest = ft_strnew(0);
			if (*line[0] != '\0')
				return (1);
			break ;
		}
		else if (s.bts < 0)
			return (-1);
	if (*rest[0] != '\0')
	{
		s.ptr = ft_initialize(rest, line, s.chr);
		*rest = ft_strdup(s.chr + 1);
		free(s.ptr);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static	t_gnl	*lst;
	t_gnl			*tp;

	if (fd < 0)
		return (-1);
	tp = lst;
	while (tp)
	{
		if (tp->fd == fd)
			return (ft_read_write(tp->fd, &tp->rest, line));
		tp = tp->next;
	}
	tp = (t_gnl*)malloc(sizeof(t_gnl));
	tp->fd = fd;
	tp->rest = ft_strnew(0);
	tp->next = lst;
	lst = tp;
	return (ft_read_write(tp->fd, &tp->rest, line));
}
