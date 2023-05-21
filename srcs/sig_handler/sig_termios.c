/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:08:20 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:08:21 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ter_attr_handler_off(void)
{
	struct termios	save;
	struct termios	attr_new;

	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &attr_new);
	attr_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &attr_new);
}

void	ter_attr_handler_on(void)
{
	struct termios	save;
	struct termios	attr_new;

	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &attr_new);
	attr_new.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &attr_new);
}
