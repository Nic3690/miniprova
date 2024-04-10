/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:53:40 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/10 19:03:25 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_lexer **lexer)
{
	char	cwd[1024];

	if (ft_strcmp((*lexer)->str, "cd") == 0)
	{
		if (chdir((*lexer)->next->str) != 0)
		{
			perror((*lexer)->next->str);
			return (0);
		}
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror((*lexer)->next->str);
			return (0);
		}
		return (1);
	}
	return (0);
}

void	builtin_pwd(t_lexer **lexer)
{
	char	cwd[1024];

	if (ft_strcmp((*lexer)->str, "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
			printf ("%s\n", cwd);
		else
			perror((*lexer)->str);
	}
}

void	builtin_echo(t_lexer **lexer)
{
	int	flag;

	flag = 1;
	if (ft_strcmp((*lexer)->str, "echo") == 0)
	{
		*lexer = (*lexer)->next;
		if (ft_strcmp((*lexer)->str, "") == 0)
		{
			printf ("\n");
			return ;
		}
		if (*lexer && ft_strcmp((*lexer)->str, "-n") == 0)
		{
			flag = 0;
			*lexer = (*lexer)->next;
		}
		while (*lexer && (*lexer)->next)
		{
			printf ("%s ", (*lexer)->str);
			*lexer = (*lexer)->next;
		}
		if (*lexer)
			printf ("%s", (*lexer)->str);
		if (flag)
			printf ("\n");
	}
}

void	bultin_env(t_lexer **lexer, t_env **env)
{
	t_lexer	*head_lexer;
	t_env	*temp;

	head_lexer = *lexer;
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
	*lexer = head_lexer;
}

void	print_env(t_lexer **lexer, t_env **env)
{
	int		i;
	t_env	*current;
	char	*temp_key;
	char	*temp_value;

	i = 0;
	current = *env;
	if (*lexer)
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

// void	bultin_temp_env(t_lexer **lexer, t_env **env)
// {
// 	int		i;
// 	t_env	*current;
// 	char	*temp_value;
// 	char	*temp_key;

// 	i = 0;
// 	current = *env;
// 	if (*lexer)
// 		*lexer = (*lexer)->next;
// 	while ((*lexer)->str[i] != '=')
// 		i++;
// 	temp_key = ft_substr((*lexer)->str, 0, i);
// 	temp_value = ft_substr((*lexer)->str, i + 1, ft_strlen((*lexer)->str));
// 	find_value(*env, temp_key, temp_value);
// 	while (current)
// 	{
// 		printf ("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}
// 	free(temp_key);
//     free(temp_value);
// }

// int find_value(t_env *env, char *temp_key, char *temp_value)
// {
//     int i;
// 	int	index;
//     t_env *temp;

// 	i = 0;
// 	temp = env;
//     index = search_map(&env, temp_key);
//     if (index != -1)
// 	{
//         while (i < index && temp != NULL)
// 		{
//             temp = temp->next;
//             i++;
//         }
//         if (temp != NULL)
// 		{
//             free(temp->value);
//             temp->value = ft_strdup(temp_value);
//         }
//     }
// 	return (0);
// }

/*Persistenza delle Modifiche: Sembrerebbe che le modifiche apportate alla lista env dovrebbero essere temporanee. Tuttavia, il codice attuale non è chiaro su come queste modifiche temporanee dovrebbero essere gestite o annullate dopo l'esecuzione del comando. La lista env viene effettivamente modificata, ma senza un meccanismo per ripristinare lo stato precedente, le modifiche rimarranno.*/