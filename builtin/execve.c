/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:39:02 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/21 13:49:15 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_execve(char **temp, char **envp)
{
	pid_t	pid;
	int		status;
	char	path[1024];

	pid = fork();
	if (pid == 0)
	{
		if (find_command(*temp, path) != 0)
		{
			printf ("Command not found: %s\n", *temp);
			exit(EXIT_FAILURE);
		}
		execve(path, temp, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

int	execute_command(char *path_env, char *command, char *path, int len)
{
    char temp[1024];
	
    ft_strncpy(temp, path_env, len);
    temp[len] = '\0';
    ft_strcat(temp, "/");
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
    char *path_env;
    char *end;
    int len;

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
			break;
        path_env = end + 1;
    }
    return (-1);
}

int	manage_builtin(t_lexer **lexer, t_env **env, t_export **export)
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
		return (builtin_export(lexer, export));
	else if (ft_strcmp((*lexer)->str, "unset") == 0)
		return (builtin_unset(lexer, export));
	else if (ft_strcmp((*lexer)->str, "exit") == 0)
		return (ft_exit((*lexer)->str));
	return (0);
}
