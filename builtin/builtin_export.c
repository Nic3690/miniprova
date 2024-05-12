/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:10:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/12 12:16:45 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_export(t_lexer **lexer, t_envp_struct *envp_struct)
{
	t_export	*head;

	head = (*envp_struct->export);
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "export") == 0)
		{
			while ((*envp_struct->export))
			{
				printf ("declare -x %s=%s\n", (*envp_struct->export)->key, (*envp_struct->export)->value);
				(*envp_struct->export) = (*envp_struct->export)->next;
			}
			(*envp_struct->export) = head;
		}
	}
	else if ((*lexer)->next)
	{
		if (ft_strcmp((*lexer)->str, "export") == 0)
			builtin_temp_export(lexer, envp_struct);
	}
	return (1);
}

void	builtin_temp_export(t_lexer **lexer, t_envp_struct *envp_struct)
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
	find_value_export(envp_struct, temp_key, temp_value);
}

void	find_value_export(t_envp_struct *envp_struct, char *temp_key, char *temp_value)
{
	int			index;
    t_export	*temp_export;
	t_env		*temp_env;
	char		*temp_env_key;
	char		*temp_env_value;

	temp_export = *(envp_struct->export);
	temp_env = *(envp_struct->env);
	temp_env_key = ft_strdup(temp_key);
	temp_env_value = ft_strdup(temp_value);
    index = search_map_export(envp_struct->export, temp_key);
    if (index != -1)
	{
		new_node_export(index, temp_export, temp_value);
		new_node_env(index, temp_env, temp_env_value);
    }
	else
	{
		new_export(envp_struct->export, temp_key, temp_value);
		ft_lstadd_back_env(&temp_env, ft_list_env(temp_env_key, temp_env_value));
	}
}

void	new_node_export(int index, t_export *temp_export, char *temp_value)
{
	int	i;

	i = 0;
	while (i < index && temp_export != NULL)
	{
		temp_export = temp_export->next;
		i++;
	}
	if (temp_export != NULL)
	{
		free(temp_export->value);
		temp_export->value = ft_strdup(temp_value);
		free(temp_value);
	}
}

void	new_node_env(int index, t_env *temp_env, char *temp_value)
{
	int	i;

	i = 0;
	while (i < index && temp_env != NULL)
	{
		temp_env = temp_env->next;
		i++;
	}
	if (temp_env != NULL)
	{
		free(temp_env->value);
		temp_env->value = ft_strdup(temp_value);
		free(temp_value);
	}
}

void	new_export(t_export **export, char *temp_key, char *temp_value)
{
	t_export	*new;
	t_export	*current;

	new = ft_list_export(temp_key, temp_value);
	if (*export == NULL || ft_strcmp((*export)->key, new->key) > 0)
	{
		new->next = *export;
		*export = new;
		free(new);
	}
	else
	{
		current = *export;
		while (current->next != NULL && ft_strcmp(current->next->key, new->key) < 0)
            current = current->next;
		new->next = current->next;
		current->next = new;
	}
}

void	bubble_sort_export(t_envp_struct *envp_struct)
{
    int 		swapped;
    t_export 	**current;
	t_export	*temp;

    swapped = 1;
    while (swapped)
	{
        swapped = 0;
        current = envp_struct->export;
        while ((*current)->next != NULL)
		{
            if (ft_strcmp((*current)->key, (*current)->next->key) > 0)
			{
                temp = (*current)->next;
                (*current)->next = (*current)->next->next;
                temp->next = *current;
                *current = temp;
                swapped = 1;
            }
            current = &(*current)->next;
        }
    }
}
