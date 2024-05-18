/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:46:54 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 14:54:46 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	manage_redirections(t_lexer **start, t_fd *fd, int process)
{
	t_lexer	*head;
	int		fd_in;
	int		fd_out;

	head = *start;
	fd_out = 0;
	fd_in = 0;
	while (*start)
	{
		if ((*start)->token && ft_strcmp((*start)->token, ">") == 0)
			fd_out = redirection_out(start, fd);
		else if ((*start)->token && ft_strcmp((*start)->token, "<") == 0)
			fd_in = redirection_in(start);
		else if ((*start)->token && ft_strcmp((*start)->token, ">>") == 0)
			fd_out = red_append(start, fd);
		else if ((*start)->token && ft_strcmp((*start)->token, "<<") == 0)
			fd_in = redirection_heredoc(start);
		*start = (*start)->next;
	}
	*start = head;
	if (fd_out == 0 && process != 0)
		free_fd(fd, fd_in);
}

int	redirection_out(t_lexer **start, t_fd *fd)
{
	int		fd_out;

	fd_out = open((*start)->next->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_out < 0)
		perror("redir_out: error while opening the file\n");
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	dup2(fd->temp, STDIN_FILENO);
	close(fd->temp);
	return (1);
}

int	redirection_in(t_lexer **start)
{
	int		fd_in;

	fd_in = open((*start)->next->str, O_RDONLY);
	if (fd_in < 0)
		perror("redir_in: error while opening the file\n");
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (fd_in);
}

int	red_append(t_lexer **start, t_fd *fd)
{
	int		fd_out;

	fd_out = open((*start)->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
		perror("redir_append: error while opening the file\n");
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	dup2(fd->temp, STDIN_FILENO);
	close(fd->temp);
	return (1);
}

void	free_fd(t_fd *fd, int fd_in)
{
	dup2(fd->fd[1], STDOUT_FILENO);
	close(fd->fd[0]);
	dup2(fd->temp, fd_in);
	close(fd->temp);
}
