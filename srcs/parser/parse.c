#include "../../headers/minishell.h"

static t_redir_args	*init_args(t_redir_args *new_redir_args)
{
	new_redir_args = malloc(sizeof(t_redir_args) * 1);
	if (!new_redir_args)
		return (NULL);
	new_redir_args->type = 0;
	new_redir_args->args = NULL;
	return (new_redir_args);
}

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd) * 1);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_args = NULL;
	new_cmd->cmd_redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static t_redir_args *new_redir_args(char *content, t_toktype type)
{
    t_redir_args *new_args = NULL;
	new_args = init_args(new_args);
    new_args->args = ft_strdup(content);
    new_args->type = type;
    new_args->next = NULL;
    return (new_args);
}

void print_t_redir_args(t_redir_args *temp)
{
	int i = 0;

	while (temp)
	{
		temp = temp->next;
		i++;
	}
}

static t_redir_args *add_args_to_list(t_redir_args **head_args, int type, char *content)
{
	t_redir_args *temp = NULL;

   
    t_redir_args *args = new_redir_args(content, type);

    if (*head_args == NULL)
    {
        *head_args = args;
    }
    else
    {
        t_redir_args *current = *head_args;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = args;
    }
	temp = *head_args;
	print_t_redir_args(temp);
	return (*head_args);
}

static void	eval_token(t_token *head, t_cmd **cmd)
{
	t_redir_args *args = NULL;
	t_token *head_ptr = NULL;
	*cmd = init_cmd();
	int i = 2;
	int j = 0;
	
	head_ptr = head;
	while (head_ptr && (t_toktype)(head->id) != TOK_PIPE)
	{
		if (head_ptr->id == TOK_WORD || head_ptr->id == TOK_D_QUOTE || head_ptr->id == TOK_S_QUOTE) //(head_ptr->id != TOK_PIPE)
		{
			while (head_ptr && (head_ptr->id == TOK_WORD || head_ptr->id == TOK_D_QUOTE || head_ptr->id == TOK_S_QUOTE)) // || head_ptr->id == TOK_DOLLAR
			{
				(*cmd)->cmd_args = add_args_to_list(&args, head_ptr->id, head_ptr->content); //&head, 
				while((*cmd)->cmd_args)
				{
					(*cmd)->cmd_args = (*cmd)->cmd_args->next;
					j++;
				}
				if (head_ptr && (head_ptr->id == TOK_REDIR_IN || head_ptr->id == TOK_REDIR_OUT || head_ptr->id == TOK_REDIR_OUT_APPEND ||
					head_ptr->id == TOK_HEREDOC))
				{
					break;
				}
				if (head_ptr && head_ptr->next)
					head_ptr = head_ptr->next;
				else
				{
					return ;
				}
			}
		}
			if (head_ptr && (head_ptr->id == TOK_REDIR_IN || head_ptr->id == TOK_REDIR_OUT || head_ptr->id == TOK_REDIR_OUT_APPEND ||
				head_ptr->id == TOK_HEREDOC))
			{
				if (head_ptr->next && head_ptr->next->id == TOK_WORD)
				{
					while (i > 0)
					{
						(*cmd)->cmd_redir = add_args_to_list(&args, head_ptr->id, head_ptr->content);
						i--;
					}
					while((*cmd)->cmd_args)
					{
						(*cmd)->cmd_args = (*cmd)->cmd_args->next;
					}
				}
			}
			else if (head_ptr->id == TOK_ERRQUOTE)
			{
				exit (0);
			}
		head_ptr = head_ptr->next;
	}
}

t_cmd	*parse(t_token *head)
{
	t_cmd	*cmd = NULL;
	t_token *temp = head;
	
	if (head && (t_toktype)(head->id) != TOK_PIPE)
		eval_token(head, &cmd);
	printf("cmd address %p\n", cmd);
	execute(cmd);
	return (cmd);
}