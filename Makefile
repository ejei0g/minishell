# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 18:45:38 by jaeylee           #+#    #+#              #
#    Updated: 2020/12/11 16:43:00 by jaeylee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
#FRAMEWORK	=	-framework OpenGL -framework AppKit
INCS		=	-I./includes -I./libft/libft
LIBS		=	-lft -L./libft
LIBFT		=	./libft

SRCS		=	./srcs/main.c \
			./srcs/parsing.c\
			./srcs/parsing_utils.c\
			./srcs/list.c\
			./srcs/env_list.c\
			./srcs/process.c\
			./srcs/implement.c\
			./srcs/echo.c\
			./srcs/gnl/get_next_line.c	\
			./srcs/gnl/get_next_line_utils.c
#SRCS_BONUS	=	./srcs_bonus/main.c

OBJS		=	$(SRCS:%.c=%.o)
#OBJS_BONUS	=	$(SRCS_BONUS:%.c=%.o)

%.o:		%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS)

all:		$(NAME)

$(NAME):	$(OBJS)
	$(MAKE) -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCS) -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:		clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re:			fclean all

.PHONY	:	all clean fclean re
