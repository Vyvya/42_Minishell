/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_red_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vg <vg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:03:54 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 01:25:03 by vg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_handle_redir_in(t_ppl **new_ppl, t_token **ptr_cmd_red)
{
	int	fd_in;

	fd_in = 0;
	if ((*ptr_cmd_red)->id == T_RI)
	{
		if (access((*ptr_cmd_red)->next->content, R_OK) != 0 && errno != ENOENT)
		{
			ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
			ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (0);
		}
		else
		{
			fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY);
			if (fd_in == -1)
				return (2);
		}
	}
	(*new_ppl)->pp_fd_in = fd_in;
	return (1);
}
