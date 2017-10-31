# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnakonec <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/29 18:03:07 by vnakonec          #+#    #+#              #
#    Updated: 2017/10/29 18:03:08 by vnakonec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CFLAGS = -Wall -Wextra -Werror

SRC = 	corewar.c corewar2.c cw_and_or_xor.c cw_ldi_lldi.c cw_live_load.c \
		cw_op_aux.c cw_op_shift_functions.c cw_sti_aff.c \
		cw_store_add_sub.c cw_zjmp_fork_lfork.c \
		data_convertor.c data_convertor2.c bot_functions.c \
		execute_functions.c execute_functions2.c \
		free_init_functions.c map_initialization.c \
		process_functions.c process_functions2.c \
		visual_functions.c visual_functions2.c \
		visual_functions3.c vm_validation.c \
		debug_functions2.c debug_functions.c

OBJ = $(SRC:.c=.o)

INCLUDES = .

LIBFT_DIR = libft/

LIB = $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME) : $(LIBFT_DIR)libft.a $(OBJ)
	@echo "\033[32mCompiling VM..."
	@gcc $(CFLAGS) -g -lncurses $(OBJ) -o $(NAME) -L./$(LIBFT_DIR) -lft
	@echo "\033[1;4;32m\n$(NAME) Created.\033[0m"

$(LIBFT_DIR)libft.a: libft/Makefile
	@echo "\033[32mCompiling VM_libft..."
	@make -C $(LIBFT_DIR)
	@echo "\033[1;4;32mVM_libft created.\033[0m"

clean:
	@echo "\033[31mRemoving objects...\033[0m"
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[1;4;31OObjects removed!\033[0m"

fclean: clean
	@echo "\033[31RRemoving corewar_vm...\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[1;4;31m$(NAME) removed!\033[0m"

re: fclean all

.PHONY: clean fclean all re
