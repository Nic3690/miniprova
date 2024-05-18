/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:39:02 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 12:55:48 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	command_execve(char **temp, char **envp)
{
	char	path[1024];

	if (find_command(*temp, path) != 0)
	{
		printf ("Command not found: %s\n", *temp);
		exit(EXIT_FAILURE);
	}
	if (execve(path, temp, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	execute_command(char *path_env, char *command, char *path, int len)
{
	char	temp[1024];

	if (len != 0)
	{
		ft_strncpy(temp, path_env, len);
		temp[len] = '\0';
		ft_strcat(temp, "/");
	}
	ft_strcat(temp, command);
	if (access(temp, X_OK) == 0)
	{
		ft_strcpy(path, temp);
		return (1);
	}
	return (0);
}

int	find_command(char *command, char *path)
{
	char	*path_env;
	char	*end;
	int		len;

	if (command[0] == '/')
	{
		execute_command("", command, path, 0);
		return (0);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (-1);
	while (path_env)
	{
		end = ft_strchr(path_env, ':');
		if (end != NULL)
			len = end - path_env;
		else
			len = ft_strlen(path_env);
		if (len > 0 && execute_command(path_env, command, path, len))
			return (0);
		if (!end)
			break ;
		path_env = end + 1;
	}
	return (-1);
}

void	check_echo(t_lexer *lexer)
{
	if (lexer->next)
	{
		if (lexer->str)
			printf ("%s ", lexer->str);
	}
	else
	{
		if (lexer->str)
			printf ("%s", lexer->str);
	}
}

int	manage_builtin(t_lexer **lexer, t_env *env)
{
	if (ft_strcmp((*lexer)->str, "cd") == 0)
		return (builtin_cd(lexer));
	else if (ft_strcmp((*lexer)->str, "pwd") == 0)
		return (builtin_pwd(lexer));
	else if (ft_strcmp((*lexer)->str, "echo") == 0)
		return (builtin_echo(lexer));
	else if (ft_strcmp((*lexer)->str, "env") == 0)
		return (builtin_env(lexer, env));
	else if (ft_strcmp((*lexer)->str, "export") == 0)
		return (builtin_export(lexer, env));
	else if (ft_strcmp((*lexer)->str, "unset") == 0)
		return (builtin_unset(lexer, env));
	else if (ft_strcmp((*lexer)->str, "exit") == 0)
		return (ft_exit(*lexer, env));
	return (0);
}
