/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:00 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/12 16:13:29 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Funzione per ottenere il valore di una variabile d'ambiente
char	*get_env_var(char *var_name, t_env *env)
{
	t_env		*current;

    if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(exit_code));
    current = env;
    while (current)
	{
        if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
        current = current->next;
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
char	*expand_env_vars(char *input, t_env *env)
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
            check_var_name(&point, &write, env);
		else
            *write++ = *point;
		point++;
    }
    *write = '\0';
    return (result);
}

void	check_var_name(char	**point, char **write, t_env *env)
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
	var_value = get_env_var(var_name, env);
	*write = copy_var_value(*write, var_value);
	(*point)--;
}

void parser_env(t_lexer **lexer, t_env *env)
{
    t_lexer *head_lexer;
    char    *expanded_str;
    char    *str;
    int     flag;
    int     i;

    head_lexer = *lexer;
    flag = 1;
    i = 0;
    while (*lexer)
    {
        str = (*lexer)->str;
        flag = 1;
        i = 0;
        while (str[i] != '\0')
        {
            if (str[i] == '\'')
                flag = !flag;
            else if (str[i] == '$' && flag)
            {
                expanded_str = expand_env_vars(str, env);
                if (expanded_str)
                {
                    free((*lexer)->str);
                    (*lexer)->str = expanded_str;
                    break ;
                }
            }
            i++;
        }
        *lexer = (*lexer)->next;
    }
    *lexer = head_lexer;  // Reset the lexer pointer back to the head after processing
}
