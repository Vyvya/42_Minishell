/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_red_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:03:49 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 22:03:50 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_handle_heredoc(t_ppl **new_ppl, t_token **ptr_cmd_red)
{
	if ((*ptr_cmd_red)->content == NULL)
		return (0);
	(*new_ppl)->pp_heredoc_eof = ft_strdup((*ptr_cmd_red)->next->content);
	return (1);
}
