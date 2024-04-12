/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:09:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/12 17:52:59 by nfurlani         ###   ########.fr       */
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
			while (temp)
			{
				printf ("%s=%s\n", temp->key, temp->value);
				temp = temp->next;
			}
			free(temp);
		}
	}
	else if ((*lexer)->next)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
			print_env(lexer, env);
	}
	return (1);
}

void	print_env(t_lexer **lexer, t_env **env)
{
	int		i;
	t_env	*current;
	char	*temp_key;
	char	*temp_value;

	i = 0;
	current = *env;
	*lexer = (*lexer)->next;
	while ((*lexer)->str[i] != '=')
		i++;
	temp_key = ft_substr((*lexer)->str, 0, i);
	temp_value = ft_substr((*lexer)->str, i + 1, ft_strlen((*lexer)->str));
	i = 0;
	while (current)
	{
		if (ft_strcmp(current->key, temp_key) == 0)
			i = printf ("%s=%s\n", current->key, temp_value);
		else
			printf ("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	if (i == 0)
		printf ("%s=%s\n", temp_key, temp_value); 
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
            // Qui dovresti anche liberare tutta la memoria allocata per new_list fino a questo punto
            return NULL;
        }
		new_node = ft_list_export(key_copy, value_copy);
        if (new_node == NULL)
		{
            free(key_copy);
            free(value_copy);
            // Anche qui, liberare la memoria allocata fino a questo punto per new_list
            return NULL;
        }
        ft_lstadd_back_export(&new_list, new_node);
        current = current->next;
    }
    return (new_list);
}
