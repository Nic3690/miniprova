/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:09:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/13 16:09:09 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_lexer **lexer, t_env *env)
{
	t_env	*temp;

	temp = env;
	
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
		{
			while (temp && temp->key)
			{
				printf ("%s=%s\n", temp->key, temp->value);
				temp = temp->next;
			}
		}
	}
	else if ((*lexer)->next)
	{
		printf("%s: %s: No such file or directory\n", (*lexer)->str, (*lexer)->next->str);
		exit_code = 127;
	}
	return (1);
}

t_env   *ft_lstcopy_env(t_env *env)
{
    t_env	*new_list;
    t_env	*head;

	new_list = NULL;
	head = env;
    while (env != NULL)
    {
        ft_lstadd_back_env(&new_list, ft_list_env(ft_strdup(env->key), ft_strdup(env->value)));
        env = env->next;
    }
	env = head;
    return (new_list);
}

int	del_first_env(t_lexer **lexer, t_env *env)
{
	t_env	*temp;

	temp = env;
	if (temp != NULL && ft_strcmp(temp->key, (*lexer)->next->str) == 0)
	{
    	temp = env->next;
        free(env->key);
        free(env->value);
        free(env);
		env = temp;
		return (1);
    }
	return (0);
}

int	del_last_env(t_lexer **lexer, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (env && env->next)
	{
    	temp = env->next;
		if (ft_strcmp(env->key, (*lexer)->next->str) == 0)
		{
			free(env->key);
			free(env->value);
			free(env);
			env = temp;
			return(0);
		}
		env = env->next;
	}
	return (1);
}

void	new_node_env(int index, t_env *env, char *temp_value)
{
	int		i;
	t_env	*head;

	i = 0;
	head = env;
	while (i < index && env != NULL)
	{
		env = env->next;
		i++;
	}
	if (env != NULL)
	{
		free(env->value);
		env->value = ft_strdup(temp_value);
		free(temp_value);
	}
	env = head;
}
