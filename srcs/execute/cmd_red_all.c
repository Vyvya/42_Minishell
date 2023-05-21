/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_red_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:03:27 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:35:52 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_red_list_size(t_token **tok_head)
{
	t_token	*tok_h;
	int		size;

	tok_h = *tok_head;
	size = 0;
	while (tok_h != NULL)
	{
		if (tok_h != NULL && (tok_h->id == T_RI || tok_h->id == T_RO \
		|| tok_h->id == T_ROA || tok_h->id == T_RHD))
			size++;
		tok_h = tok_h->next;
	}
	return (size);
}

static int	handle_redirection(t_ppl **new_ppl, t_token **ptr_cmd_red)
{
	if ((*ptr_cmd_red)->id == T_RO)
		return (ft_handle_redir_out(new_ppl, ptr_cmd_red));
	else if ((*ptr_cmd_red)->id == T_ROA)
		return (ft_handle_redir_append(new_ppl, ptr_cmd_red));
	else if ((*ptr_cmd_red)->id == T_RI)
		return (ft_handle_redir_in(new_ppl, ptr_cmd_red));
	else if ((*ptr_cmd_red)->id == T_RHD)
	{
		ft_handle_heredoc(new_ppl, ptr_cmd_red);
		(*new_ppl)->pp_heredoc_status = 1;
		return (1);
	}
	return (1);
}

int	ft_handle_red_all(t_ppl **new_ppl, t_token *ptr_cmd_red)
{
	int	i;
	int	red_list_size;
	int	res;

	i = 0;
	res = 0;
	red_list_size = ft_red_list_size(&ptr_cmd_red);
	while (ptr_cmd_red && i < red_list_size)
	{
		res = handle_redirection(new_ppl, &ptr_cmd_red);
		if (res != 1)
			return (res);
		if (ptr_cmd_red->next->next)
			ptr_cmd_red = ptr_cmd_red->next->next;
		i++;
	}
	free_token_list(ptr_cmd_red);
	return (res);
}
