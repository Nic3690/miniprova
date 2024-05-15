# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 15:17:34 by nfurlani          #+#    #+#              #
#    Updated: 2024/05/15 22:50:22 by nfurlani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc -g -o

CFLAGS		=	-Werror -Wall -Wextra -fsanitize=address

# READLINE	=	-L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
READLINE	=	-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline

SRCS		=	main.c signal.c \
				lexer/quotes.c lexer/split_token.c \
				parser/parser.c parser/lst_lexer.c parser/parser_env.c parser/lst_env.c \
				builtin/free.c builtin/pipe.c builtin/builtin_utils.c builtin/builtin_utils2.c builtin/builtin_env.c builtin/builtin_export.c builtin/heredoc.c builtin/commands.c builtin/execve.c builtin/redirections.c builtin/check_error.c \
				utils/utils.c utils/utils2.c utils/utils3.c utils/utils4.c utils/utils5.c \

HEADER		=	includes/

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

export CPPFLAGS := -I/opt/homebrew/opt/readline/include
export LDFLAGS := -L/opt/homebrew/opt/readline/lib

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) -I $(HEADER) $(OBJS) -o $(NAME) $(READLINE)

clean		:
				rm -f $(OBJS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
