/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:10:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/14 11:50:02 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_env(t_env *env)
// {
// 	t_env	*head;

// 	head = env;
// 	while (env)
// 	{
// 		printf("%s ----- %s\n", env->key, env->value);
// 		env = env->next;
// 	}
// 	env = head;
// }

int	builtin_export(t_lexer **lexer, t_env *env)
{
	t_env	*head;
	t_env	*copy;

	head = env;
	copy = ft_lstcopy_env(env);
	bubble_sort_export(&copy);
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "export") == 0)
		{
			while (copy)
			{
				printf ("declare -x %s=%s\n", copy->key, copy->value);
				copy = copy->next;
			}
			env = head;
		}
	}
	else if ((*lexer)->next)
	{
		if (ft_strcmp((*lexer)->str, "export") == 0)
			builtin_temp_export(lexer, env);
	}
	ft_free_env(copy);
	return (1);
}

void	builtin_temp_export(t_lexer **lexer, t_env *env)
{
	int			i;
	char		*temp_value;
	char		*temp_key;

	i = 0;
	*lexer = (*lexer)->next;
	while ((*lexer)->str[i] != '=')
		i++;
	temp_key = ft_substr((*lexer)->str, 0, i);
	temp_value = ft_substr((*lexer)->str, i + 1, ft_strlen((*lexer)->str));
	find_value_env(env, temp_key, temp_value);
}

void	find_value_env(t_env *env, char *temp_key, char *temp_value)
{
	int			index;
	t_env		*temp_env;

	temp_env = env;
	index = search_map_env(env, temp_key);
	if (index != -1)
		new_node_env(index, env, temp_value);
	else
		ft_lstadd_back_env(&temp_env, ft_list_env(temp_key, temp_value));
}

void	swap_nodes(t_env **head, t_env *prev, t_env *current, t_env *next)
{
	if (prev != NULL)
		prev->next = next;
	else
		*head = next;
	current->next = next->next;
	next->next = current;
}

void	bubble_sort_export(t_env **head)
{
	int		swapped;
	t_env	*prev;
	t_env	*current;
	t_env	*temp;

	prev = NULL;
	swapped = 1;
	current = *head;
	temp = NULL;
	while (swapped)
	{
		swapped = 0;
		prev = NULL;
		current = *head;
		while (current != NULL && current->next != NULL)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				temp = current->next;
				swap_nodes(head, prev, current, temp);
				prev = temp;
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
