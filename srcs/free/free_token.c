/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:10:22 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:10:23 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_token_list(t_token *tokens)
{
	t_token	*cur;
	t_token	*next;

	cur = tokens;
	next = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		my_free(cur->content);
		my_free(cur);
		cur = next;
	}
}
