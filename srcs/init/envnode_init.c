/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envnode_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:10:07 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:10:08 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_envnode	*init_envnode(void)
{
	t_envnode	*env_node;

	env_node = ft_calloc(1, sizeof(t_envnode));
	if (!env_node)
	{
		ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
		msg_error("minishell_VH: error memory", errno);
	}
	return (env_node);
}
