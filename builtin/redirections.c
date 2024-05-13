/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:46:54 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/12 16:40:43 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_redirections(t_lexer **lexer, t_env *env, char **envp)
{
	int		fd;
	t_lexer	*head;

	fd = 0;
	head = *lexer;
	while (*lexer)
	{
		if (ft_check_token((*lexer)->token) && ft_strcmp((*lexer)->token, "|"))
		{
			if (count_lexer(lexer) > 2)
			{
				printf ("%s: %s: No such file or directory\n", head->str, (*lexer)->next->str);
				return ;
			}
			if (count_lexer(lexer) == 0)
			{
				printf ("zsh: parse error near '\\n'\n");
				return ;
			}
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	execute_redirection(lexer, env, envp, fd);
}

void	execute_redirection(t_lexer **lexer, t_env *env, char **envp, int fd)
{
	t_lexer	*head;

	head = *lexer;
	redirection_out(lexer, env, envp, fd);
	*lexer = head;
	redirection_in(lexer, env, envp, fd);
	*lexer = head;
	redirection_append(lexer, env, envp, fd);
	*lexer = head;
	redirection_heredoc(lexer, env, envp);
	*lexer = head;
}

void	redirection_out(t_lexer **lexer, t_env *env, char **envp, int fd)
{
	t_lexer	*start;
	int		copy;
	char	**temp;

	copy = dup(STDOUT_FILENO);
	start = new_start_redirection(lexer);
	temp = new_temp_redirection(start);
	while (*lexer)
	{
		if (ft_strcmp((*lexer)->token, ">") == 0)
		{
			fd = open((*lexer)->next->str, O_CREAT | O_WRONLY, 0644);
			if (fd < 0)
				return (perror("minishell: redir_out: error while opening the file\n"));
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (manage_builtin(&start, env) != 1)
				command_execve(temp, envp);
			dup2(copy, STDOUT_FILENO);
			close(copy);
		}
		*lexer = (*lexer)->next;
	}
	ft_free(temp);
	ft_free_lexer(&start);
}

void	redirection_in(t_lexer **lexer, t_env *env, char **envp, int fd)
{
	t_lexer	*start;
	char	**temp;
	int		copy;

	copy = dup(STDIN_FILENO);
	start = new_start_redirection(lexer);
	temp = new_temp_redirection(start);
	while (*lexer)
	{
		if (ft_strcmp((*lexer)->token, "<") == 0)
		{
			fd = open((*lexer)->next->str, O_RDONLY);
			if (fd < 0)
				return perror("minishell: redir_in: error while opening the file\n");
			dup2(fd, STDIN_FILENO);
			close(fd);
			if (manage_builtin(&start, env) != 1)
				command_execve(temp, envp);
			dup2(copy, STDIN_FILENO);
			close(copy);
		}
		*lexer = (*lexer)->next;
	}
	ft_free(temp);
	ft_free_lexer(&start);
}

void	redirection_append(t_lexer **lexer, t_env *env, char **envp, int fd)
{
	t_lexer	*start;
	int		copy;
	char	**temp;

	copy = dup(STDOUT_FILENO);
	start = new_start_redirection(lexer);
	temp = new_temp_redirection(start);
	while (*lexer)
	{
		if (ft_strcmp((*lexer)->token, ">>") == 0)
		{
			fd = open((*lexer)->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror("minishell: redir_append: error while opening the file\n"));
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (manage_builtin(&start, env) != 1)
				command_execve(temp, envp);
			dup2(copy, STDOUT_FILENO);
			close(copy);
		}
		*lexer = (*lexer)->next;
	}
	ft_free(temp);
	ft_free_lexer(&start);
}
