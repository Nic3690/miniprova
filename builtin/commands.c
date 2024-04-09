/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:53:40 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/09 19:02:22 by nfurlani         ###   ########.fr       */
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
	t_env	*head_env;
	t_lexer	*head_lexer;

	head_env = *env;
	head_lexer = *lexer;
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
		{
			while (*env)
			{
				printf ("%s=%s\n", (*env)->key, (*env)->value);
				*env = (*env)->next;
			}
			*env = head_env;
		}
	}
	else if ((*lexer)->next)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
			bultin_temp_env(lexer, env);
	}
	*lexer = head_lexer;
}

void	bultin_temp_env(t_lexer **lexer, t_env **env)
{
	int		i;
	int		index;
	t_env	*head;
	char	*temp_value;
	char	*temp_key;

	i = 0;
	head = *env;
	*lexer = (*lexer)->next;
	while ((*lexer)->str[i] != '=')
		i++;
	temp_key = ft_substr((*lexer)->str, 0, i);
	temp_value = ft_substr((*lexer)->str, i + 1, ft_strlen((*lexer)->str));
	index = search_map(env, temp_key);
	i = -1;
	if (index != -1)
	{
		while (++i < index && *env != NULL)
			*env = (*env)->next;
		if (*env != NULL)
			(*env)->value = ft_strdup(temp_value);
	}
	free(temp_key);
    free(temp_value);
	*env = head;
}

/*Persistenza delle Modifiche: Sembrerebbe che le modifiche apportate alla lista env dovrebbero essere temporanee. Tuttavia, il codice attuale non è chiaro su come queste modifiche temporanee dovrebbero essere gestite o annullate dopo l'esecuzione del comando. La lista env viene effettivamente modificata, ma senza un meccanismo per ripristinare lo stato precedente, le modifiche rimarranno.*/