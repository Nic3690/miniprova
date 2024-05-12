/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:09:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/12 15:58:00 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_lexer **lexer, t_env **env)
{
	t_env	*temp;

	temp = *env;
	
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
		{
			while (temp && temp->key)
			{
				printf ("%s=%s\n", temp->key, temp->value);
				temp = temp->next;
			}
			// free(temp);
		}
	}
	else if ((*lexer)->next)
	{
		printf("%s: %s: No such file or directory\n", (*lexer)->str, (*lexer)->next->str);
		exit_code = 127;
	}
	return (1);
}

t_export   *ft_lstcopy_env(t_env *env)
{
    t_export	*new_list;
    t_env		*current;
	t_export	*new_node;
	char		*key_copy;
	char		*value_copy;

	new_list = NULL;
	current = env;
    while (current != NULL)
    {
        key_copy = ft_strdup(current->key);
        value_copy = ft_strdup(current->value);
        if (key_copy == NULL || value_copy == NULL)
        {
            free(key_copy);
            free(value_copy);
            return NULL;
        }
		new_node = ft_list_export(key_copy, value_copy);
        if (new_node == NULL)
		{
            free(key_copy);
            free(value_copy);
            return NULL;
        }
        ft_lstadd_back_export(&new_list, new_node);
        current = current->next;
    }
    return (new_list);
}

t_env   *ft_lstcopy_env(t_export *env)
{
    t_export	*new_list;
    t_env		*current;
	t_export	*new_node;
	char		*key_copy;
	char		*value_copy;

	new_list = NULL;
	current = env;
    while (current != NULL)
    {
        key_copy = ft_strdup(current->key);
        value_copy = ft_strdup(current->value);
        if (key_copy == NULL || value_copy == NULL)
        {
            free(key_copy);
            free(value_copy);
            return NULL;
        }
		new_node = ft_list_export(key_copy, value_copy);
        if (new_node == NULL)
		{
            free(key_copy);
            free(value_copy);
            return NULL;
        }
        ft_lstadd_back_export(&new_list, new_node);
        current = current->next;
    }
    return (new_list);
}
