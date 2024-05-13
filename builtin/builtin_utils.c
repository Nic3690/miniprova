/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:42:26 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/13 17:01:10 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*new_start(t_lexer **lexer)
{
	t_lexer	*start;
	t_lexer	*head;
	t_lexer	*start_head;

	head = *lexer;
	start = malloc(sizeof(t_lexer));
	start_head = start;
	while (!ft_strchr((*lexer)->token, '|') && *lexer && (*lexer)->next)
	{
		start->str = ft_strdup((*lexer)->str);
		start->token = ft_strdup("");
		start->next = malloc(sizeof(t_lexer));
		start = start->next;
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	start = start_head;
	return (start);
}

char	**new_temp(t_lexer *start)
{
	t_lexer	*head;
	char	**temp;
	int		i;

	head = start;
	i = 0;
	temp = malloc(sizeof(char *) * 1024 + 1);
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
		if (ft_strchr((*lexer)->token, '|'))
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
		if (ft_strcmp((*lexer)->token, ">") == 0
			|| ft_strcmp((*lexer)->token, "<") == 0
			|| ft_strcmp((*lexer)->token, ">>") == 0
			|| ft_strcmp((*lexer)->token, "<<") == 0)
		{
			*lexer = head;
			return (1);
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (0);
}
