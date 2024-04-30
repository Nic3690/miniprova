/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:00 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/30 18:39:22 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Funzione per ottenere il valore di una variabile d'ambiente
char	*get_env_var(char *var_name, t_envp_struct *envp_struct)
{
	t_env		*current;
	t_export	*current_export;

    if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(envp_struct->exit_status));
    current = *(envp_struct->env);
    while (current)
	{
        if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
        current = current->next;
    }
    current_export = *(envp_struct->export);
    while (current_export)
	{
        if (ft_strcmp(current_export->key, var_name) == 0)
			return (current_export->value);
        current_export = current_export->next;
    }
    return (getenv(var_name));
}

// Funzione per copiare il valore di una variabile nella stringa risultato
char	*copy_var_value(char *write, char *var_value)
{
    if (var_value)
	{
        ft_strcpy(write, var_value);
        return (write + ft_strlen(var_value));
    }
    return (write);
}

// Funzione per espandere le variabili d'ambiente in una stringa
char	*expand_env_vars(char *input, t_envp_struct *envp_struct)
{
    int		len;
	char	*result;
	char	*write;
	char	*point;
	
	len = ft_strlen(input);
    result = malloc((len * 2 + 1) * sizeof(char));
    if (!result)
		return NULL;
    write = result;
	point = input;
	while (*point)
    {
        if (*point == '$')
            check_var_name(&point, &write, envp_struct);
		else
            *write++ = *point;
		point++;
    }
    *write = '\0';
    return result;
}

void	check_var_name(char	**point, char **write, t_envp_struct *envp_struct)
{
	char	*var_start;
	char	var_name[100];
	char	*var_value;
	int		var_len;

	(*point)++;
	var_start = *point;
	while (**point && (ft_isalnum(**point) || **point == '_' || **point == '?'))
		(*point)++;
	var_len = *point - var_start;
	ft_strncpy(var_name, var_start, var_len);
	var_name[var_len] = '\0';
	var_value = get_env_var(var_name, envp_struct);
	*write = copy_var_value(*write, var_value);
	(*point)--;
}

void	parser_env(t_lexer **lexer, t_envp_struct *envp_struct)
{
    t_lexer *head_lexer;
	char	*expanded_str;

	head_lexer = *lexer;
    while (*lexer)
	{
        if (count_quotes((*lexer)->str, '\'') != 2)
		{
            expanded_str = expand_env_vars((*lexer)->str, envp_struct);
            if (expanded_str)
			{
                free((*lexer)->str);
                (*lexer)->str = expanded_str;
            }
        }
        (*lexer) = (*lexer)->next;
    }
    *lexer = head_lexer;
}
