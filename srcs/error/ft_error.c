/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:59:12 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 21:59:13 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_error_print(char **arg)
{
	printf("Bash: ");
	printf("%s", arg[0]);
	printf(": ");
	printf("Command not found");
	printf("\n");
	g_exit_status = 127;
	return (1);
}
