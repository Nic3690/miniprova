/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:39:02 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/12 17:19:41 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_execve(t_lexer **lexer, t_env **env, t_export **export, char **temp, char **envp)
{
	pid_t	pid;
	int		status;
	char	path[1024];
	char	*command;

	if (manage_bultin(lexer, env, export) == 1)
		return ;
	command = *temp;
	pid = fork();
	if (pid == 0)
	{
		if (find_path(command, path) != 0)
		{
			printf ("Command not found: %s\n", command);
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


int	find_path(char *command, char *path)
{
	char	*path_env;
	char	*start;
	char	*end;
	int		len;
	char	temp[1024];
	
	path_env = getenv("PATH");
	if (!path_env)
		return (-1);
	start = path_env;
	while (start)
	{
		end = ft_strchr(start, ':');
		if (end != NULL)
			len = end - start;
		else
			len = ft_strlen(start);
		if (len > 0)
		{
			ft_strncpy(temp, start, len);
			temp[len] = '\0';
			ft_strcat(temp, "/");
			ft_strcat(temp, command);
			if (access(temp, X_OK) == 0)
			{
				ft_strcpy(path, temp);
				return (0);
			}
		}
		if (!end)
			break ;
		start = end + 1;
	}
	return (-1);
}

int	manage_bultin(t_lexer **lexer, t_env **env, t_export **export)
{
	if (ft_strcmp((*lexer)->str, "cd") == 0)
	{
		builtin_cd(lexer);
		return (1);
	}
	else if (ft_strcmp((*lexer)->str, "pwd") == 0)
	{
		builtin_pwd(lexer);
		return (1);
	}
	else if (ft_strcmp((*lexer)->str, "echo") == 0)
	{
		builtin_echo(lexer);
		return (1);
	}
	else if (ft_strcmp((*lexer)->str, "env") == 0)
	{
		builtin_env(lexer, env);
		return (1);
	}
	else if (ft_strcmp((*lexer)->str, "export") == 0)
	{
		builtin_export(lexer, export);
		return (1);
	}
	else if (ft_strcmp((*lexer)->str, "unset") == 0)
	{
		bultin_unset(lexer, export);
		return (1);
	}
	return (0);
}
