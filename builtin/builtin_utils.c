/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:42:26 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 14:53:13 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*new_start(t_lexer **lexer)
{
	t_lexer	*start;
	t_lexer	*head;

	head = *lexer;
	start = NULL;
	while (*lexer && ft_strcmp((*lexer)->token, "|") != 0 && *lexer)
	{
		if ((*lexer)->str)
			ft_lstadd_back(&start, ft_lstnew(ft_strdup((*lexer)->str), NULL));
		if ((*lexer)->token)
			ft_lstadd_back(&start, ft_lstnew(NULL, ft_strdup((*lexer)->token)));
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (start);
}

char	**new_full_temp(t_lexer **lexer)
{
	char	**temp;
	char	**head;
	t_lexer	*head_lexer;
	int		size;

	size = 1024;
	head_lexer = *lexer;
	temp = malloc(sizeof(char *) * size + 1);
	head = temp;
	if (temp == NULL)
		return (NULL);
	while (*lexer)
	{
		if ((*lexer)->str != NULL)
			*temp = ft_strdup((*lexer)->str);
		if ((*lexer)->token != NULL)
			*temp = ft_strdup((*lexer)->token);
		*lexer = (*lexer)->next;
		temp++;
	}
	*temp = NULL;
	temp = head;
	*lexer = head_lexer;
	return (temp);
}

int	check_pipe(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if (ft_strcmp((*lexer)->token, "|") == 0)
		{
			*lexer = head;
			return (1);
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (0);
}

int	check_redirection(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if ((*lexer)->token && (ft_strcmp((*lexer)->token, ">") == 0
				|| ft_strcmp((*lexer)->token, "<") == 0
				|| ft_strcmp((*lexer)->token, ">>") == 0
				|| ft_strcmp((*lexer)->token, "<<") == 0))
		{
			*lexer = head;
			return (1);
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (0);
}
