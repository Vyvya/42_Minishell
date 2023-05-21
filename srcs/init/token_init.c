/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:10:14 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:10:15 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*init_token(t_token	*token)
{
	token = my_malloc(sizeof(t_token) * 1);
	if (!token)
		return (0);
	token->content = NULL;
	token->id = 0;
	token->next = NULL;
	return (token);
}
