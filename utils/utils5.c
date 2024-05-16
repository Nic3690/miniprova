/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:40:08 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/16 18:38:21 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	pipe_counter(t_lexer **lexer)
// {
// 	int		i;
// 	t_lexer	*head;

// 	i = 1;
// 	head = *lexer;
// 	while (*lexer)
// 	{
// 		if (ft_strcmp((*lexer)->token, "|") == 0)
// 			i++;
// 		*lexer = (*lexer)->next;
// 	}
// 	*lexer = head;
// 	return (i);
// }

int	check_char(t_lexer **lexer, char *str)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if ((*lexer)->token && ft_strcmp((*lexer)->token, str) == 0)
		{
			*lexer = head;
			return (1);
		}
		(*lexer) = (*lexer)->next;
	}
	*lexer = head;
	return (0);
}

int	ft_check_all_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\"') || (str[i] == '\''))
			return (1);
		i++;
	}
	return (0);
}
