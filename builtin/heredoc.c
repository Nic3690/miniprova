/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:53:05 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 15:35:54 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	manage_heredoc(t_lexer **lexer)
{
	t_lexer	*head;
	char	*temp;
	char	*str;

	head = *lexer;
	while ((*lexer) && (*lexer)->next)
	{
		if ((*lexer)->token && ft_strcmp((*lexer)->token, "<<") == 0)
		{
			str = ft_strdup((*lexer)->next->str);
			free((*lexer)->next->str);
			(*lexer)->next->str = NULL;
			readline_heredoc(str, lexer);
			temp = ft_strdup((*lexer)->next->str);
			free((*lexer)->next->str);
			(*lexer)->next->str = ft_strjoin_heredoc(temp, "");
			free(temp);
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}

void	readline_heredoc(char *str, t_lexer **lexer)
{
	char	*input;
	char	*temp;

	while (1)
	{
		input = readline("heredoc> ");
		if (*input)
		{
			if (ft_strcmp(input, str) == 0)
			{
				free(str);
				free(input);
				break ;
			}
			temp = ft_strjoin_heredoc((*lexer)->next->str, input);
			free((*lexer)->next->str);
			(*lexer)->next->str = ft_strdup(temp);
			free(input);
			if (temp != NULL)
			{
				free(temp);
				temp = NULL;
			}
		}
	}
}

int	redirection_heredoc(t_lexer **start)
{
	int		fd;

	fd = open("prova.txt", O_CREAT | O_RDWR, 0664);
	if (fd < 0)
		perror("minishell: redir_in: error while opening the file\n");
	write(fd, (*start)->next->str, ft_strlen((*start)->next->str));
	close(fd);
	fd = open("prova.txt", O_RDONLY);
	if (fd < 0)
		perror("minishell: redir_in: error while opening the file\n");
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("prova.txt");
	return (fd);
}

char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!s2)
		return (0);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!str)
		return (0);
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[n] != '\0')
		str[i++] = s2[n++];
	if (*s2)
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}
