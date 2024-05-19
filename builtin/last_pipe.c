/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:14:18 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/19 17:20:48 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	last_command(t_lexer **start, t_fd *fd, t_env *env, char **envp)
{
	char	**temp;
	t_lexer	*command;

	command = new_start_redirection(start);
	temp = new_temp_redirection(command);
	fd->pid = fork();
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
	if (fd->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (fd->pid == 0)
	{
		child_last_process(fd, start);
		if (manage_builtin(start, env) != 1)
			command_execve(temp, envp);
		else
			exit(g_exit_code);
	}
	else
		last_process(fd, start, env);
	ft_free(temp);
	ft_free_lexer(&command);
}

void	child_last_process(t_fd *fd, t_lexer **start)
{
	if (check_redirection(start))
		manage_redirections(start, fd, 0);
	else
	{
		dup2(fd->temp, STDIN_FILENO);
		close(fd->temp);
	}
}

void	last_process(t_fd *fd, t_lexer **start, t_env *env)
{
	close(fd->fd[0]);
	close(fd->fd[1]);
	close(fd->temp);
	while (waitpid(-1, &g_exit_code, WUNTRACED) != -1)
		;
	if (ft_strcmp((*start)->str, "exit") == 0)
		ft_exit(*start, env);
	close(fd->temp);
	fd->temp = dup(0);
}
