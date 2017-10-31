/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:02:14 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/05/15 20:17:50 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include "../includes/libft.h"

typedef struct	s_lst
{
	int		i;
	char	*buf;
	char	flags[6];
	int		width;
	int		precision;
	char	mod[2];
	char	type;
	int		counter;
	int		(*g_funcs[123])(struct s_lst *, va_list);
}				t_lst;

int				ft_printf(const char *format, ...);
void			ft_funcs_arr(t_lst *list);
int				ft_zero(t_lst *list);
int				ft_type_d_i(t_lst *list, va_list ap);
int				ft_type_u_o_x(t_lst *list, va_list ap);
int				ft_type_p(t_lst *list, va_list ap);
int				ft_type_c_s(t_lst *list, va_list ap);
int				ft_type_big_u_o(t_lst *list, va_list ap);
int				ft_type_big_s(t_lst *list, va_list ap);
void			ft_precision_digits(t_lst *l);
void			ft_precision_character(t_lst *list);

#endif
