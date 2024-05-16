/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:07:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/16 13:08:27 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*new_start_redirection(t_lexer **lexer)
{
	t_lexer	*start;
	t_lexer	*head;

	head = *lexer;
	start = NULL;
	while (!ft_check_token((*lexer)->token) && *lexer && (*lexer)->next)
	{
		ft_lstadd_back(&start, ft_lstnew(ft_strdup((*lexer)->str), NULL));
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (start);
}

char	**new_temp_redirection(t_lexer *start)
{
	t_lexer	*head;
	char	**temp;
	int		i;

	head = start;
	i = 0;
	temp = malloc(sizeof(char *) * 1024);
	while (start)
	{
		if (start->str != NULL)
			temp[i++] = ft_strdup(start->str);
		start = start->next;
	}
	temp[i] = NULL;
	start = head;
	return (temp);
}

int	count_lexer(t_lexer **lexer)
{
	int		i;
	t_lexer	*head;

	i = 0;
	head = *lexer;
	*lexer = (*lexer)->next;
	while ((*lexer) && !ft_check_token((*lexer)->token))
	{
		*lexer = (*lexer)->next;
		i++;
	}
	*lexer = head;
	return (i);
}

void	init_prev(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer && (*lexer)->next)
	{
		(*lexer)->next->prev = *lexer;
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}

char	*copy_var_value(char *write, char *var_value)
{
	if (var_value)
	{
		ft_strcpy(write, var_value);
		return (write + ft_strlen(var_value));
	}
	return (write);
}
