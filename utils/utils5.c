/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:40:08 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/15 21:12:07 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_counter(t_lexer **lexer)
{
	int		i;
	t_lexer	*head;

	i = 1;
	head = *lexer;
	while (*lexer)
	{
		if (ft_strcmp((*lexer)->token, "|") == 0)
			i++;
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (i);
}