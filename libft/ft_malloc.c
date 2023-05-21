/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:44:35 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 14:44:36 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**finder(void)
{
	static t_list	*wrm;

	return (&wrm);
}

void	*my_malloc(unsigned long size)
{
	char	*buffer;
	t_list	*new_elem;

	buffer = malloc(size);
	if (!buffer)
	{
		destroy_all();
		ft_putstr("ERROR my_malloc\n");
		exit (1);
	}
	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
	{
		free(buffer);
		destroy_all();
		ft_putstr("ERROR my_malloc\n");
		exit (1);
	}
	new_elem->content = buffer;
	new_elem->next = 0;
	ft_lstadd_back(finder(), new_elem);
	return (buffer);
}

int	my_free(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	prev = 0;
	wrstart = finder();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*wrstart = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	destroy_all(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	wrstart = finder();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*wrstart = 0;
}
