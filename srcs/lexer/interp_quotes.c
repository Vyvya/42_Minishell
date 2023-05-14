#include "../../headers/minishell.h"

int	is_q(char c)
{
	if (c == '\'' || c == '"')
	{
		return (1);
	}
	return (0);
}

int	eval_q_t(char *q)
{
	if (*q == '\"')
		return (T_DQ);
	else if (*q == '\'')
		return (T_SQ);
	return (0);
}

static void advance(char **p_q, int *q_len)
{
	(*p_q)++;
	(*q_len)++;
}

// static char	*manage_close(char **p, t_token **head, char **p_q, int *q_len)
// {
// 	(*q_len)++;
// 	if (((eval_q_t(*p)) + (eval_q_t((*p_q)))) % 2 == 0)
// 		add_token(head, ft_substr(*p, 0, (*q_len)), eval_q_t(*p));
// 		*p += (*q_len);
// 	return (*p);
// }

char *check_quotes(char **p, t_token **head)
{
	char *p_q;
	int	q_status;
	int q_len;

	p_q = *p;
	q_status = 0;
	q_len = 0;
	while (p_q && *p_q)
	{
		if (q_status == CLOSED)
		{
			q_status = OPEN;
			advance(&p_q, &q_len);
			while (*p_q && (!(is_q(*p_q)) || ((eval_q_t(*p)) + (eval_q_t(p_q))) % 2))
				advance(&p_q, &q_len);
		}
		else if (is_q(*p_q) && q_status == OPEN)
		{
			q_status = CLOSED;
			q_len++;
			if (((eval_q_t(*p)) + (eval_q_t(p_q))) % 2 == 0)
				add_token(head, ft_substr(*p, 0, q_len), eval_q_t(*p));
				*p += q_len;
			return (*p);
		}
	}
	if (!(is_q(*p_q)) && q_status == OPEN && *p_q == '\0')
	{
		add_token(head, ft_substr(*p, 0, (*p - p_q)), T_ERQ);
		*p += q_len;
		return (*p);
	}
	else
		return (*p);
}

// char *check_quotes(char **p, t_token **head)
// {
//     char *p_q;
//     int q_len;
// 	int	q_status;

// 	p_q = *p;
//     while (p_q && *p_q)
// 	{
//         if (q_status == CLOSED)
// 		{
//             q_status = OPEN;
//             p_q++;
//             q_len++;
//             p_q = handle_open_quote(p, head, &p_q, &q_len);
//         }
// 		else if (is_q(*p_q) && q_status == OPEN)
// 		{
//             q_status = CLOSED;
//             process_closed_quote(p, head, &p_q, q_len);
//             return *p;
//         }
//     }
//     return handle_end_of_input(p, head, &p_q, q_len);
// }
