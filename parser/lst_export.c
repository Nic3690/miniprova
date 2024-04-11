/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:45:23 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/11 12:47:45 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_export	*ft_list_export(char *key, char *value)
{
	t_export	*new;

	new = (t_export *)ft_calloc(1, sizeof(t_export));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_export(t_export **lst, t_export *new)
{
	t_export	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast_export(*lst);
	temp->next = new;
}

t_export	*ft_lstlast_export(t_export *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
