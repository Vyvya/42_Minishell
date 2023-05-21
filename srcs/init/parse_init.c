/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:10:11 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:10:12 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)my_malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->cmd_word = NULL;
	new_cmd->cmd_red = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
