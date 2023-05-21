/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:07:56 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:07:57 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	manage_curr(t_token **temp, t_token **curr)
{
	(*temp) = (*curr);
	(*curr) = (*curr)->next;
	my_free((*temp)->content);
	my_free((*temp));
}

void	*delete_tok_spaces(t_token **token_head)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*temp;

	curr = *token_head;
	prev = NULL;
	while (curr != NULL)
	{
		if (curr->id == T_SP)
		{
			if (prev != NULL)
				prev->next = curr->next;
			else
				*token_head = curr->next;
			manage_curr(&temp, &curr);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (0);
}
