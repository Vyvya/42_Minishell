#include "../../headers/minishell.h"

int	handle_input_red_error()
{
	char	*msg;

	msg = NULL;
	printf("Z\n");
	// msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", (*tok_h)->content);
	ft_putstr_fd("minishell_VH: syntax error near unexpected token `newline'\n", STDERR_FILENO);
	// ft_putstr_fd(msg, STDERR_FILENO);
	// ft_putstr_fd("\'\n", STDERR_FILENO);
	g_exit_status = 258;
	// ft_putstr_fd(R "ERROR input REDIR\n" RS, STDERR_FILENO);
	// ft_putstr_fd("ERROR input PIPE 2\n", STDERR_FILENO);
// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
// tok_h->id = TOK_ERROR;
	return (EXIT_SUCCESS);

}

int	handle_input_error(t_token **token_head)
{
	t_token *tok_h;
	char	*msg;

	tok_h = *token_head;
	if (tok_h != NULL && tok_h->id == TOK_PIPE)
	{
		printf("0\n");
		printf("ft_token_list_size(&tok_h): %d\n", ft_token_list_size(&tok_h));
		// ft_putstr_fd("ERROR input PIPE 1\n", STDERR_FILENO);
		// msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", "|");
		ft_putstr_fd("minishell_VH: syntax error near unexpected token `|\'\n", STDERR_FILENO);
		// ft_putstr_fd(msg, STDERR_FILENO);
		// ft_putstr_fd("\'\n", STDERR_FILENO);
		g_exit_status = 258;
		// printf("g_exit_status: %d\n", g_exit_status);
		return (1);
		// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
	}
	while (tok_h != NULL)
	{
		if (tok_h->id == TOK_R_OUT_APP || tok_h->id == TOK_R_HDOC || \
			tok_h->id == TOK_R_OUT || tok_h->id == TOK_R_IN)
		{
			if (tok_h->next == NULL || tok_h->next->id != TOK_WORD)
			{
				printf("0a\n");
				handle_input_red_error();
				printf("0b\n");
				return (1);
			}
		}
		if (tok_h && tok_h->id == TOK_PIPE && tok_h->next && tok_h->next->id == TOK_PIPE)
			// g_exit_status = 1;
		{
			printf("1\n");

			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			// ft_putstr_fd(tok_h->content, STDERR_FILENO);
			// msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			// ft_putstr_fd(msg, STDERR_FILENO);
			// ft_putstr_fd("\'\n", STDERR_FILENO);
			ft_putstr_fd("minishell_VH: syntax error near unexpected token `||\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
			return (1);
		}
		if (tok_h != NULL && (tok_h->id == TOK_R_OUT || tok_h->id == TOK_R_IN || tok_h->id == TOK_R_OUT_APP || tok_h->id == TOK_R_HDOC)
		 && (tok_h->next && tok_h->next->id == TOK_PIPE))
		{
			printf("2\n");
			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			ft_putstr_fd(msg, STDERR_FILENO);
			ft_putstr_fd("\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
			return (1);	
		}
		if (tok_h != NULL && last_token(tok_h)->id == TOK_PIPE)
		{
			printf("3\n");

			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			// msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			// ft_putstr_fd(msg, STDERR_FILENO);
			// ft_putstr_fd("\'\n", STDERR_FILENO);
			ft_putstr_fd("minishell_VH: syntax error near unexpected token `|\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 1); //syntax error (near unexpected token `|')

			// ft_putstr_fd("ERROR input last PIPE\n", STDERR_FILENO);
			// tok_h->id = TOK_ERROR;
			return (1);
		}
		if (tok_h != NULL && tok_h->id == TOK_ERROR)
		{
			printf("4\n");

			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			ft_putstr_fd(msg, STDERR_FILENO);
			ft_putstr_fd("\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
			return (1);
		}
		if (tok_h != NULL && tok_h->id == TOK_ERRQUOTE)
		{
			printf("5\n");

			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			ft_putstr_fd(msg, STDERR_FILENO);
			ft_putstr_fd("\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
			return (1);	
		}
		
		else
			tok_h = tok_h->next;	
	}
	return (0);
}
