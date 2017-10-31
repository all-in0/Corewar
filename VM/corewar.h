/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <dbezsinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 03:36:15 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/10/28 10:13:17 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

# include "libft/includes/libft.h"
# include <stdio.h>
# include <ncurses.h>

# define NEW_S(x, size) 		(x*)ft_memalloc(sizeof(x) * (size))
# define NEW(x) 				(x*)ft_memalloc(sizeof(x))

# define MAX_N_ARGS				3
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define NUM_CMDS				17
# define WT_UNSET				20000
# define MAP_SIZE_MOD(x) 		(x) % MEM_SIZE
# define MAX_STEP_MOD(x)		(x) % IDX_MOD
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define BAD_ARG_MASK			16
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define PAIR_WW				64
# define M_PAIR					0
# define C_PAIR					4
# define H_PAIR					8
# define DL						cw_draw_line
# define CGB					get_nbrby_id

typedef char			t_arg_type;

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_bot
{
	int					id : 4;
	t_header			*header;
	int					name;
	t_byte				reg[REG_NUMBER][REG_SIZE];
	unsigned int		last_live_cycle;
	unsigned int		lives_in_period;
}						t_bot;

typedef	struct			s_process
{
	int					ps_id;
	int					wait;
	int					parent;
	t_byte				reg[REG_NUMBER][REG_SIZE];
	int					pc : 16;
	unsigned int		carry : 1;
	unsigned int		is_alive : 1;
	unsigned int		num_lives : 16;
	t_byte				cur_op;
	struct s_process	*next;
}						t_process;

typedef struct			s_cw_map
{
	unsigned char		*memory;
	unsigned char		*mem_style;
	int					num_players : 8;
	int					num_bots_init;
	t_bot				**players;
	t_process			*process;
	t_process			*suspended_proc;
	unsigned int		lives_count;
	unsigned int		proc_count;
	int					cur_cycle;
	int					cycle_to_die;
	int					next_check;
	int					checks_perf : 8;
	char				*error_msg;
	int					dump_cycle;
	unsigned int		f_disp : 1;
	unsigned int		is_paused : 1;
	unsigned short		cps;
}						t_cw_map;

typedef struct			s_op
{
	char				*name;
	unsigned int		num_args : 8;
	char				arg_mask[MAX_N_ARGS];
	int					op_code : 8;
	unsigned short int	cycle_cost;
	char				*descr;
	unsigned int		codage_octal : 1;
	unsigned int		mod_carry : 1;
	unsigned int		label_size : 1;
}						t_op;

t_cw_map				init_map(unsigned int n);
void					error_call(char *msg);
void					free_map(t_cw_map *map);
void					check_bot_number(int bot_i, int *bot_nbr,
									int (*bot_nums)[4]);
void					debug_announce_bots(t_cw_map *map);
void					print_map(unsigned char *map);
t_byte					cw_debug_print_reg(t_byte reg[REG_SIZE]);
void					cw_debug_draw_opc(int y, int op_code);
int						cw_bot_nbrtoi(t_cw_map *map, int bot_nbr);
void					cw_debug_msg_box(char *msg, int i);
void					cw_debug_msg_box2(char *msg, int i);
void					cw_debug_msg_box3(char *msg, int i);
void					cw_debug_msg_box4(char *msg, int i);
void					cw_debug_msg_box_line(char *msg, int i, int line);
void					cw_debug_msg_box_line_alive(char *msg, int i, int line,
									int is_alive);
void					cw_debug_msgbox_aff(int value);
void					cw_debug_disp_regs(t_byte regs[REG_NUMBER][REG_SIZE],
									int id);
unsigned short			read_commands(unsigned char *mem_adr);
void					reverse_bytes(int *bytes, int size);
void					cw_set_reg_rev(t_byte (*reg)[REG_SIZE], int bot_name);
void					cw_cpy_regs(t_byte (*reg)[REG_SIZE],
									t_byte reg_p[REG_SIZE]);
void					fill_map_data(t_cw_map *map, int ac, char **av);
int						is_cmd_flag(char *str);
void					save_bot(t_cw_map *map, int bot_nbr, int bot_i,
									char *f_name);
t_byte					print_bots_stats(t_cw_map *map);
int						cw_getnbr_byid(int id, t_cw_map *map);
void					create_process(t_cw_map *map, t_process *parent,
									int bot, int position);
void					cw_suspend_process(t_cw_map *map, int ps_id);
void					cw_visualizer(t_cw_map *map);
void					cw_set_map_style(unsigned char *styles, t_bot *bot,
									int offset);
void					cw_scr_redraw(t_cw_map *map);
void					cw_debug_move_pc(t_process *ps, t_byte *style);
t_byte					cw_draw_info(t_cw_map *map);
void					cw_degug_show_key(t_byte key);
void					cw_disp_winner(char *name, int cycle, int bot_id,
									int nbr);
void					cw_put_proc_style(unsigned char *style, t_process *ps);
void					cw_put_single_proc_style(unsigned char *style,
									t_process *ps);
t_byte					cw_get_swap_pair(t_byte pair, t_byte pair_offset);
t_byte					cw_move_ps_pc(t_byte *style, t_process *ps,
									int pc_offset);
t_byte					cw_highlight_color(t_byte *style, int pos, int pair);
t_byte					cw_run_fight_v(t_cw_map *map);
t_byte					cw_run_fight(t_cw_map *map);
t_byte					cw_execute_process(t_cw_map *map);
t_byte					cw_check_lives(t_cw_map *map);
t_byte					cw_getpc_shift(t_byte *map, int pc, t_op *op,
									int *shift);
int						cw_get_coctal(int op_code, t_byte *mem, int pc);
int						cw_map_move(int cur_pos, int shift);
t_byte					cw_checkreg_num(t_byte reg_num);
t_byte					cw_clean_process(t_cw_map *map);
t_byte					cw_show_dump(t_cw_map *map);
int						cw_get_dir_arg(t_cw_map *map, int current_index,
									int is_short);
int						cw_get_reg_arg(t_cw_map *map, t_process *p, int cur);
int						cw_get_ind_arg(t_cw_map *map, t_process *p, int cur);
t_byte					cw_put_intin_reg(t_process *p, int value,
									t_byte regnum);
t_byte					cw_refresh_index(int *updatable, int updater,
									int concatenator);
short					cw_get_ind_value(t_cw_map *map, int cur);
int						cw_live(t_cw_map *map, t_process *p);
int						cw_load(t_cw_map *map, t_process *p);
int						cw_store(t_cw_map *map, t_process *p);
int						cw_add(t_cw_map *map, t_process *p);
int						cw_sub(t_cw_map *map, t_process *p);
int						cw_and(t_cw_map *map, t_process *p);
int						cw_or(t_cw_map *map, t_process *p);
int						cw_xor(t_cw_map *map, t_process *p);
int						cw_zjump(t_cw_map *map, t_process *p);
int						cw_load_idx(t_cw_map *map, t_process *p);
int						cw_store_idx(t_cw_map *map, t_process *p);
int						cw_fork(t_cw_map *map, t_process *p);
int						cw_long_load(t_cw_map *map, t_process *p);
int						cw_long_load_idx(t_cw_map *map, t_process *p);
int						cw_long_fork(t_cw_map *map, t_process *p);
int						cw_aff(t_cw_map *map, t_process *p);
int						get_arg_mask(int a_type);
int						get_arg_size(unsigned short a_mask,
									unsigned int l_size);
int						get_max_arg_size(unsigned short a_mask, t_op *op);
void					cw_cpy_reg(t_process *proc, unsigned char r1,
											unsigned char r2);
void					cw_putreg_onmap(t_cw_map *map, unsigned char *reg,
									int i, t_process *p);
char					cw_fill_reg(t_cw_map *map, t_process *p,
									int regn, int i);
void					cw_adjust_cps(t_byte keycode, unsigned short *cps);
void					init_bot_colors(int n_bots);
void					cw_put_bot_stat(t_bot **bots, int num_p);
t_byte					cw_vm_stop(t_cw_map *map);
void					push_process(t_process **list, t_process *n);
t_process				*pop_process(t_process **prev_el);
t_process				*pop_top_process(t_process **list);

#endif
