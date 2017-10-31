# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnakonec <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/29 20:57:18 by vnakonec          #+#    #+#              #
#    Updated: 2017/10/29 20:57:20 by vnakonec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FLAGS = -Wall -Wextra -Werror -O3

SRC = 	asm_main.c asm_parse_file.c \
	asm_addition_funcs.c asm_error_and_free.c \
	asm_instruncions_lable.c asm_work_with_args.c \
	asm_write_bytes_in_file.c asm_parse_init_validate.c

OBJ = $(SRC:.c=.o)

INCLUDES = .

LIBFT_DIR = Libft_extended/

all: $(NAME)

$(NAME) : $(LIBFT_DIR)libft.a $(OBJ)
	@echo "\033[32mCompiling ASM..."
	@gcc $(CFLAGS) -g -lncurses $(OBJ) -o $(NAME) -L./$(LIBFT_DIR) -lft
	@echo "\033[1;4;32m\n$(NAME) Created.\033[0m"

$(LIBFT_DIR)libft.a: Libft_extended/Makefile
	@echo "\033[32mCompiling ASM_libft..."
	@make -C $(LIBFT_DIR)
	@echo "\033[1;4;32mASM_libft created.\033[0m"

clean:
	@echo "\033[31mRemoving objects...\033[0m"
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[1;4;31OObjects removed!\033[0m"

fclean: clean
	@echo "\033[31RRemoving corewar_ASM...\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[1;4;31m$(NAME) removed!\033[0m"

re: fclean all

.PHONY: clean fclean all re
