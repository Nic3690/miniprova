/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:10:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/11 23:29:23 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_export   *ft_lstcopy_env(t_env *env)
{
    t_export	*new_list;
    t_env		*current;
	t_export	*new_node;
	char		*key_copy;
	char		*value_copy;

	new_list = NULL;
	current = env;
    while (current != NULL)
    {
        key_copy = ft_strdup(current->key);
        value_copy = ft_strdup(current->value);
        if (key_copy == NULL || value_copy == NULL)
        {
            free(key_copy);
            free(value_copy);
            // Qui dovresti anche liberare tutta la memoria allocata per new_list fino a questo punto
            return NULL;
        }
		new_node = ft_list_export(key_copy, value_copy);
        if (new_node == NULL)
		{
            free(key_copy);
            free(value_copy);
            // Anche qui, liberare la memoria allocata fino a questo punto per new_list
            return NULL;
        }
        ft_lstadd_back_export(&new_list, new_node);
        current = current->next;
    }
    return (new_list);
}

void	builtin_export(t_lexer **lexer, t_export **export)
{
	t_export	*head;

	head = *export;
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "export") == 0)
		{
			while (*export)
			{
				printf ("%s=%s\n", (*export)->key, (*export)->value);
				*export = (*export)->next;
			}
			*export = head;
		}
	}
	else if ((*lexer)->next)
	{
		if (ft_strcmp((*lexer)->str, "export") == 0)
			builtin_temp_export(lexer, export);
	}
}

void	builtin_temp_export(t_lexer **lexer, t_export **export)
{
	int			i;
	char		*temp_value;
	char		*temp_key;

	i = 0;
	*lexer = (*lexer)->next;
	while ((*lexer)->str[i] != '=')
		i++;
	temp_key = ft_substr((*lexer)->str, 0, i);
	temp_value = ft_substr((*lexer)->str, i + 1, ft_strlen((*lexer)->str));
	find_value_export(export, temp_key, temp_value);
}

void find_value_export(t_export **export, char *temp_key, char *temp_value)
{
    int			i;
	int			index;
    t_export	*temp;

	i = 0;
	temp = *export;
    index = search_map_export(export, temp_key);
    if (index != -1)
	{
        while (i < index && temp != NULL)
		{
            temp = temp->next;
            i++;
        }
        if (temp != NULL)
		{
			free(temp->value);
            temp->value = ft_strdup(temp_value);
		}
    }
	else
		new_export(export, temp_key, temp_value);
}

void	new_export(t_export **export, char *temp_key, char *temp_value)
{
	t_export	*new;
	t_export	*current;
	
	new = ft_list_export(temp_key, temp_value);
	if (*export == NULL || ft_strcmp((*export)->key, new->key) > 0)
	{
		new->next = *export;
		*export = new;
	}
	else
	{
		current = *export;
		while (current->next != NULL && ft_strcmp(current->next->key, new->key) < 0)
            current = current->next;
		new->next = current->next;
		current->next = new;
	}
}

void bubble_sort_export(t_export **export)
{
    if (!export || !*export) return; // Se la lista è vuota o ha un solo elemento, non fare nulla.

    int swapped;
    t_export *prev, *curr, *next, *temp_head = NULL;

    // Continua a passare attraverso la lista finché ci sono scambi.
    while (1) {
        swapped = 0; // Resetta lo stato degli scambi per questa iterazione.
        prev = NULL;
        curr = *export;

        // Mentre non siamo alla fine della lista...
        while (curr->next != temp_head) {
            next = curr->next;
            if (ft_strcmp(curr->key, next->key) > 0) {
                // Scambio necessario per mantenere l'ordine alfabetico.
                swapped = 1; // Segnala che è avvenuto uno scambio.
                curr->next = next->next; // Aggiorna i puntatori per lo scambio.
                next->next = curr;
                if (prev) prev->next = next; // Collega il nodo precedente al nodo successivo (ora diventato precedente).
                else *export = next; // Aggiorna la testa della lista se lo scambio è avvenuto all'inizio.

                // Aggiorna i puntatori per il prossimo passaggio.
                prev = next;
            } else {
                // Se non è necessario scambiare, semplicemente avanza.
                prev = curr;
                curr = next;
            }
        }
        if (!swapped) break; // Se non ci sono stati scambi, la lista è ordinata.
        temp_head = curr; // Ottimizzazione: riduci la parte della lista da ordinare nel prossimo passaggio.
    }
}

// void	bubble_sort_export(t_export **export)
// {
//     int 		swapped;
//     t_export 	**current;
// 	t_export	*temp;

//     swapped = 1;
//     while (swapped)
// 	{
//         swapped = 0;
//         current = export;
//         while ((*current)->next != NULL)
// 		{
//             if (ft_strcmp((*current)->key, (*current)->next->key) > 0)
// 			{
//                 temp = (*current)->next;
//                 (*current)->next = (*current)->next->next;
//                 temp->next = *current;
//                 *current = temp;
//                 swapped = 1;
//             }
//             current = &(*current)->next;
//         }
//     }
// }

/*mettere in ordine alfabetico*/
/*aggiungere declare -x porcoddio*/