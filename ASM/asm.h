/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 21:25:51 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/10/16 20:25:02 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "Libft_extended/includes/libft.h"
# include "op.h"
# include <fcntl.h>
# include <stdlib.h>

# define TAB(x) (x == ' ' || x == '\t' || x == '\n')
# define SIZE 50000
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct			s_file
{
	char				*str;
	int					row;
	struct s_file		*next;
}						t_file;

typedef struct			s_label
{
	char				*label;
	int					byte;
	struct s_label		*next;
}						t_label;

typedef struct			s_variable
{
	char				*variable;
	int					current_byte;
	int					start_byte;
	int					size_arg;
	struct s_variable	*next;
}						t_variable;

typedef struct			s_asm
{
	char				*name_cor;
	unsigned char		*data;
	int					st_byte;
	int					i;
	int					count_rows;
	char				**split;
	int					arg[3];
	int					flag_name;
	int					flag_comm;
	int					error;
	int					malloc_s;
	t_label				*label;
	t_variable			*variable;
	t_file				*file;
	t_header			*header;
}						t_asm;

/*
** asm_main.h
*/

void					asm_parse_program(char *s, t_file *st, t_asm *as);
void					asm_read_file(char *av, t_asm *as);
void					check_name(char *av);

/*
**  asm_addition_funcs.c
*/

t_label					*search_label(t_asm *as, char *str);
char					*remove_comment_in_end(t_asm *as, char *s);
char					*asm_trim(char *str);
int						index_list(t_asm *as);
void					asm_validate_end_str(char *str, t_file *st);

/*
** asm_parse_file.c
*/

t_file					*asm_parse_name_2(char *s, t_file *st, t_asm *as);
t_file					*asm_parse_name(char *s, t_file *st, t_asm *as);
t_file					*asm_parse_comm_2(char *s, t_file *st, t_asm *as);
t_file					*asm_parse_comm(char *s, t_file *st, t_asm *as);
void					asm_parse_name_comm(t_asm *as);

/*
**  asm_instruncions_label.c
*/

void					asm_save_label(t_asm *as, t_file *st, char *s, int l);
void					asm_save_variable(t_asm *as, char *s, int size_byte);
int						asm_variable(t_asm *as, char *s, int size_byte);
void					asm_parse_instruction(char *s, t_file *st, t_asm *as);
void					asm_instruction(char *s, t_file *st, t_asm *as,
						int index);

/*
** asm_work_with_args.c
*/

void					asm_t_dir(t_asm *as, t_file *st, char *s, int index);
void					asm_t_reg(t_asm *as, t_file *st, char *s);
void					asm_t_ind(t_asm *as, t_file *st, char *s);
void					asm_parse_arg(t_file *st, t_asm *as, int index);
void					asm_arg(t_asm *as);

/*
** asm_parse_init_validate.c
*/

void					init_struct(t_asm *as);
void					asm_parse_name_comm_additional(char *s,
						t_asm *as, int flag);
void					asm_validate_coma(char *s, t_asm *as,
						t_file *st, int index);
int						asm_work_with_split(t_asm *as, char *s);
void					asm_validate_label_char(char *s, t_asm *as, t_file *st);

/*
** asm_write_bytes_in_file.c
*/

void					asm_write_magic_prog_size(int fd, unsigned value);
void					asm_write_in_file(t_asm *as);
void					asm_coding_arg(t_asm *as, unsigned value, int n);
int						asm_coding_number_arg(t_asm *as, int index);
void					asm_rewrite_variable_in_data(t_asm *as);

/*
** asm_error_and_free.c
*/

void					asm_free_variable_label_file(t_variable *variable,
						t_label *label, t_file *file);
void					asm_free_struct(t_asm *as);
void					asm_error(char *s, t_file *st, t_asm *as);
void					asm_lseek(int fd, t_asm *as);
int						asm_atoi(char *str, t_file *st, t_asm *as);

#endif
