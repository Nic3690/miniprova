/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:03:41 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/05 16:44:48 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// t_built	*split_command(t_lexer **lexer)
// {
// 	t_lexer	*head;
// 	t_built	*built;
// 	char	*command;
// 	char	*flag;
// 	char	*params;

// 	built = NULL;
// 	head = *lexer;
// 	while (*lexer)
// 	{
// 		while (ft_strchr((*lexer)->token, '|') == 0)
// 		{
// 			manage_command();
// 			command = ft_strdup((*lexer)->str);
// 			(*lexer) = (*lexer)->next;
// 		}
// 		*lexer = (*lexer)->next;
// 	}
// 	printf ("%s\n", built->command);
// 	printf ("%s\n", built->flag);
// 	printf ("%s\n", built->params);
// 	*lexer = head;
// 	return (built);
// }

// 		// while (ft_strchr((*lexer)->token, '|') == 0)
// /*se il primo lexer è un token di tipo << non deve prendere il primo di comando*/

// // void	prova(t_lexer **lexer)
// // {
// // 	t_lexer	*head;

// // 	head = *lexer;	
// // 	while (*lexer && (*lexer)->token != '|')
// // 	{
// // 		if (ft_strcmp((*lexer)->str, "echo") == 0)
// // 		{
// // 			(*lexer) = (*lexer)->next;
// // 			printf ("%s\n", (*lexer));
// // 		}
// // 		(*lexer) = (*lexer)->next;
// // 	}
// // 	*lexer = head;
// // }

// void	check_built(char *str)
// {
// 	if (ft_strcmp (char *str))
// }

// t_built	*ft_list_built(char *command, char *flag, char *params)
// {
// 	t_built	*new;

// 	(void)flag;
// 	(void)params;
// 	new = (t_built *)ft_calloc(1, sizeof(t_built));
// 	if (new == NULL)
// 		return (NULL);
// 	new->command = command;
// 	new->flag = flag;
// 	new->next = NULL;
// 	return (new);
// }

// void	ft_lstadd_back_built(t_built **lst, t_built *new)
// {
// 	t_built	*temp;

// 	if (!new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	temp = ft_lstlast_built(*lst);
// 	temp->next = new;
// }

// t_built	*ft_lstlast_built(t_built *lst)
// {
// 	while (lst)
// 	{
// 		if (lst->next == NULL)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }