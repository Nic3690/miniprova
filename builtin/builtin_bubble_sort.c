/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bubble_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:18:49 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/19 16:45:23 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap(t_env **head, t_env **prev, t_env **current, t_env **temp)
{
	*temp = (*current)->next;
	if (*prev != NULL)
		(*prev)->next = *temp;
	else
		*head = *temp;
	(*current)->next = (*temp)->next;
	(*temp)->next = *current;
	*prev = *temp;
}

void	reassign(t_env **prev, t_env **current, int *swapped, t_env *head)
{
	*prev = NULL;
	*current = head;
	if (*swapped == 1)
		*swapped = 0;
	else
		*swapped = 1;
}

void	bubble_sort_export(t_env **head)
{
	int		swapped;
	t_env	*prev;
	t_env	*current;
	t_env	*temp;

	temp = NULL;
	reassign(&prev, &current, &swapped, *head);
	while (swapped)
	{
		reassign(&prev, &current, &swapped, *head);
		while (current != NULL && current->next != NULL)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap(head, &prev, &current, &temp);
				swapped = 1;
			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
	}
}
