/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:58:46 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 17:01:05 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	error_env(void)
{
	printf("Failed to create my_environment list\n");
	g_exit_status = 1;
}

void	error_args(void)
{
	printf("Error arguments\n");
	g_exit_status = 1;
}

void	msg_error(char *error, int errnum)
{
	g_exit_status %= 256;
	if (error)
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(g_exit_status);
	}
	else
	{
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	ft_putstr_fd("Exit status: ", STDERR_FILENO);
	ft_putnbr_fd(g_exit_status, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(0);
}
