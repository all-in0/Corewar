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


NAME	=	corewar

VMDIR	=	VM

ASMDIR	=	ASM

.PHONY	:	re clean fclean all ASM VM

all		:	$(NAME)

$(NAME)	:	VM ASM

VM		:
		@make -C $(VMDIR)
		@cp $(VMDIR)/corewar ./

ASM		:
		@make -C $(ASMDIR)
		@cp $(ASMDIR)/asm ./

clean	:	VMCL ASMCL

VMCL	:
		@make -C $(VMDIR) clean

ASMCL	:
		@make -C $(ASMDIR) clean

fclean	:	VMFCL ASMFCL

VMFCL	:
		@make -C $(VMDIR) fclean
		@rm -f ./corewar
ASMFCL	:
		@make -C $(ASMDIR) fclean
		@rm -f ./asm
re		:	fclean all
