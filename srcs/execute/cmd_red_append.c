/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_red_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:03:42 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 22:03:43 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_handle_redir_append(t_ppl **new_ppl, t_token **ptr_cmd_red)
{
	int	fd_out;

	fd_out = -1;
	if ((*ptr_cmd_red)->id == T_ROA)
	{
		if (access((*ptr_cmd_red)->next->content, F_OK) == 0)
		{
			if (access((*ptr_cmd_red)->next->content, W_OK) != 0)
			{
				ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
				ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				return (0);
			}
		}
		fd_out = open((*ptr_cmd_red)->next->content, \
		O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd_out == -1)
			return (-1);
	}
	(*new_ppl)->pp_fd_out = fd_out;
	return (1);
}
