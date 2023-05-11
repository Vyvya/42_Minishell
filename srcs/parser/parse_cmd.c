#include "../../headers/minishell.h"

static int	build_word_red_cmd(t_cmd **new_cmd, t_token *tok_h)
{
	while (tok_h != NULL)
	{
		if (tok_h->id == TOK_PIPE)
			break;
		if (tok_h->id == TOK_REDIR_OUT || tok_h->id == TOK_REDIR_IN ||
			tok_h->id == TOK_REDIR_OUT_APPEND	|| tok_h->id == TOK_HEREDOC)
		{
			if (tok_h->next == NULL || tok_h->next->id != TOK_WORD)
			{
				ft_putstr_fd("minishell_VH: syntax error near unexpected token `newline'\n", STDERR_FILENO);
				// ft_putstr_fd(R "ERROR input REDIR\n" RS, STDERR_FILENO);
				// ft_putstr_fd("ERROR input PIPE 2\n", STDERR_FILENO);
				g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
				return (-1);
			}
			ft_token_list_addback(&(*new_cmd)->cmd_red, new_token(tok_h->content, tok_h->id));
			ft_token_list_addback(&(*new_cmd)->cmd_red, new_token(tok_h->next->content, TOK_WORD));
			tok_h = tok_h->next; // skip the word that follows the redirection token
		}
		else
		{
			// add token to cmd_word list
			ft_token_list_addback(&(*new_cmd)->cmd_word, new_token(tok_h->content, tok_h->id));
		}

		tok_h = tok_h->next;
	}
	return (0);
}

void	*build_cmd_list(t_token **tok_cmd_list)
{
	t_token	*tok_h;
	t_cmd	*cmd_list = NULL;
	t_cmd	*cmd_tail = NULL;
	t_cmd	*new_cmd = NULL;

	int i = 0;
	while (tok_cmd_list[i] != NULL)
	{
		tok_h = tok_cmd_list[i];
		new_cmd = init_cmd();
		if (build_word_red_cmd(&new_cmd, tok_h) == -1)
			return (0);
		if (cmd_list == NULL) {
			cmd_list = new_cmd;
			cmd_tail = new_cmd;
		} else {
			cmd_tail->next = new_cmd;
			cmd_tail = new_cmd;
		}
		i++;
	}
	return (cmd_list);
}
