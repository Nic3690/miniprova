# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 15:17:34 by nfurlani          #+#    #+#              #
#    Updated: 2024/03/09 17:18:04 by nfurlani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g

SRCS		=	main.c parser.c quotes.c parser_token.c split_token.c utils.c utils2.c utils3.c utils4.c

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