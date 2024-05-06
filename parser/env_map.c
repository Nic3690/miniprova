/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:39:04 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/05 10:45:23 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_map_export(t_export **export, char *str)
{
	int			index;
	t_export	*head;

	index = 0;
	head = *export;
	while (*export)
	{
		if (ft_strcmp((*export)->key, str) == 0)
		{
			*export = head;
			return (index);
		}
		index++;
		(*export) = (*export)->next;
	}
	*export = head;
	return (-1);
}
