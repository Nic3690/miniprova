# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 15:17:34 by nfurlani          #+#    #+#              #
#    Updated: 2024/05/05 17:42:11 by nfurlani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g

SRCS		=	main.c \
				lexer/quotes.c lexer/split_token.c \
				parser/env_map.c parser/parser.c parser/lst_lexer.c parser/parser_env.c parser/lst_env.c parser/lst_export.c \
				builtin/free.c builtin/pipe.c builtin/builtin_utils.c builtin/builtin_utils2.c builtin/builtin_env.c builtin/builtin_export.c builtin/heredoc.c builtin/commands.c builtin/execve.c builtin/redirections.c \
				utils/utils.c utils/utils2.c utils/utils3.c utils/utils4.c \

OBJS		=	$(SRCS:.c=.o)

LDFLAGS		=	-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean		:
				rm -r $(OBJS)

fclean		:	clean
				rm $(NAME)

re			:	fclean all
