# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 15:17:34 by nfurlani          #+#    #+#              #
#    Updated: 2024/04/12 15:45:40 by nfurlani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g

SRCS		=	main.c \
				lexer/quotes.c lexer/split_token.c \
				parser/parser.c parser/lst_lexer.c parser/parser_token.c parser/parser_env.c parser/lst_env.c parser/lst_export.c \
				builtin/builtin.c builtin/builtin_env.c builtin/builtin_export.c builtin/heredoc.c builtin/commands.c builtin/execve.c \
				utils/utils.c utils/utils2.c utils/utils3.c \

OBJS		=	$(SRCS:.c=.o)

LDFLAGS		=	-lreadline

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm $(NAME)

re			:	fclean all