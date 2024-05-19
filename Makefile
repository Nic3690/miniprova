# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 15:17:34 by nfurlani          #+#    #+#              #
#    Updated: 2024/05/19 17:23:23 by nfurlani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc -g -o

CFLAGS		=	-Werror -Wall -Wextra

READLINE	=	-L/usr/include -lreadline

SRCS		=	main.c \
				parser/parser.c parser/lst_lexer.c parser/parser_env.c parser/lst_env.c parser/quotes.c \
				builtin/free.c builtin/pipe.c builtin/last_pipe.c builtin/builtin_utils.c builtin/builtin_utils2.c builtin/builtin_env.c builtin/builtin_export.c builtin/builtin_bubble_sort.c builtin/heredoc.c builtin/commands.c builtin/execve.c builtin/redirections.c \
				utils/utils.c utils/utils2.c utils/utils3.c utils/utils4.c utils/utils5.c \

HEADER		=	includes/

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) -I $(HEADER) $(OBJS) -o $(NAME) $(READLINE)

clean		:
				rm -f $(OBJS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
