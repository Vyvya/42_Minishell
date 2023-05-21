/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vg <vg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:59:03 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 01:15:04 by vg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	input_error_02(t_token **tok_head)
{
	t_token	*tok_h;

	tok_h = *tok_head;
	if (((tok_h != NULL && tok_h->id == T_ERR) || (tok_h != NULL && \
	tok_h->id == T_ERQ)) || (tok_h != NULL && (tok_h->id == T_RO || \
	tok_h->id == T_RI || tok_h->id == T_ROA || tok_h->id == T_RHD) && \
	(tok_h->next && tok_h->next->id == T_PP)))
	{
		handle_input_red_pipe(&tok_h->content);
		return (1);
	}
	return (0);
}

int	input_error_01(t_token **tok_head)
{
	t_token	*tok_h;

	tok_h = *tok_head;
	if (tok_h->id == T_ROA || tok_h->id == T_RHD || \
			tok_h->id == T_RO || tok_h->id == T_RI)
	{
		if (tok_h->next == NULL || tok_h->next->id != T_W)
		{
			handle_input_red_error();
			return (1);
		}
	}
	if (tok_h && tok_h->id == T_PP && tok_h->next && \
	tok_h->next->id == T_PP)
	{
		handle_input_2pipes();
		return (1);
	}
	if (tok_h != NULL && last_token(tok_h)->id == T_PP)
	{
		handle_input_pipe();
		return (1);
	}
	return (0);
}

int	handle_input_error(t_token **token_head)
{
	t_token	*tok_h;

	tok_h = *token_head;
	if (tok_h != NULL && tok_h->id == T_PP)
	{
		handle_input_pipe();
		return (1);
	}
	while (tok_h != NULL)
	{
		if (input_error_01(&tok_h))
			return (1);
		if (input_error_02(&tok_h))
			return (1);
		else
			tok_h = tok_h->next;
	}
	return (0);
}
