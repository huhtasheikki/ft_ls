# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/24 18:09:10 by hhuhtane          #+#    #+#              #
#    Updated: 2020/10/20 14:47:17 by hhuhtane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIBFT = libft.a
LIBFT_DIR = libft/
LIBFT_H = -I./libft/includes/

SRC = ft_ls.c \
		ft_list_dir.c \
		ft_parse_args.c \
		error_ls.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

SRC_DIR = srcs/
OBJ_DIR = obj/
INC_DIR = includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

COLOR_RESET = \033[0m
COLOR_WAIT = \033[0;31m
COLOR_OK = \033[0;32m
COLOR_TITLE = \033[1;37m

all : $(NAME)

$(NAME):
		@rm -f a.out
		@echo "FT_LS \t\t[$(COLOR_TITLE)Make started$(COLOR_RESET)]"
		@make -C $(LIBFT_DIR)
		@cp $(LIBFT_DIR)$(LIBFT) ./$(LIBFT)
		@$(CC) $(CFLAGS) $(LIBFT_H) $(SRCS) $(LIBFT)

test: fclean all
		$(CC) $(LIBFT_H) $(NAME) main.c

clean:
		@make clean -C $(LIBFT_DIR)
		@echo "REMOVE $(COLOR_TITLE)$(OBJ)$(COLOR_RESET)"
		@rm -f $(OBJ)
		@find . -type f -name '.DS_Store' -delete
		@find . -type f -name '*~' -print -delete -o -name "#*#" -print -delete

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		@rm -f $(NAME)
		@rm -f a.out

re: fclean all
