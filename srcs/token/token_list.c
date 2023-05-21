/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:07:44 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:07:45 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_token_list_size(t_token **tok_head)
{
	t_token	*tok_h;
	int		size;

	tok_h = *tok_head;
	size = 0;
	while (tok_h != NULL)
	{
		if (tok_h != NULL)
			size++;
		tok_h = tok_h->next;
	}
	return (size);
}

void	ft_token_list_addback(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_token(t_token **head, char *content, t_toktype type)
{
	t_token	*token;
	t_token	*curr;

	token = NULL;
	curr = NULL;
	token = new_token(content, type);
	if (*head == NULL)
		*head = token;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = token;
		token->next = NULL;
	}
}

t_token	*last_token(t_token *token_list)
{
	t_token	*curr;

	if (token_list == NULL)
		return (NULL);
	curr = token_list;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}
