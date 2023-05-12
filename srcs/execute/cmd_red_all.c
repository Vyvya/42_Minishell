#include "../../headers/minishell.h"

static int	ft_red_list_size(t_token **tok_head)
{
	t_token	*tok_h;
	int		size;

	tok_h = *tok_head;
	size = 0;
	while (tok_h != NULL)
	{
		if (tok_h != NULL && (tok_h->id == TOK_R_IN || tok_h->id == TOK_R_OUT \
		|| tok_h->id == TOK_R_OUT_APP || tok_h->id == TOK_R_HDOC))
			size++;
		tok_h = tok_h->next;
	}
	return (size);
}

void	handle_redirection(t_ppl **new_ppl, t_token **ptr_cmd_red)
{
	if ((*ptr_cmd_red)->id == TOK_R_OUT)
		ft_handle_redir_out(new_ppl, ptr_cmd_red);
	else if ((*ptr_cmd_red)->id == TOK_R_OUT_APP)
		ft_handle_redir_append(new_ppl, ptr_cmd_red);
	else if ((*ptr_cmd_red)->id == TOK_R_IN)
	{
		if (ft_handle_redir_in(new_ppl, ptr_cmd_red) == 1)
			return ;
		else
			return ;
	}
	else if ((*ptr_cmd_red)->id == TOK_R_HDOC)
	{
		(*new_ppl)->pp_heredoc_status = 1;
		ft_handle_heredoc(new_ppl, ptr_cmd_red);
	}
}

int	ft_handle_red_all(t_ppl **new_ppl, t_token *ptr_cmd_red)
{
	int	i;
	int	red_list_size;

	i = 0;
	red_list_size = ft_red_list_size(&ptr_cmd_red);
	while (ptr_cmd_red && i < red_list_size)
	{
		handle_redirection(new_ppl, &ptr_cmd_red);
		if (ptr_cmd_red->next->next)
			ptr_cmd_red = ptr_cmd_red->next->next;
		i++;
	}
	free_token_list(ptr_cmd_red);
	return (1);
}
