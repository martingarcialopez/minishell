#include "../includes/builtins.h"
#include "../includes/tree.h"
#include "../includes/libft.h"


static t_token			g_token_tab[] = {
	{"|", pipeline},
	{"<", left_redirection},
	{">", right_redirection},
	{";", semicolon},
	{"&", and},
	{"\'", single_quote},
	{"\"", double_quote},
	{"\\", backslash},
	{" ", space},
	{"$", variable},
	{"?", status},
	{">>", double_right_redirection},
	{"&&", double_and},
	{"||", or},
	{0, 0}	
};

void				free_token(void *tkn)
{
	t_token *token;

	token = (t_token*)tkn;
	free(token->value);
	free(token);
}

//probablemente la funcion con mas leaks de minishell. gg
t_list				*line_to_token_list(char *line)
{
	t_list		*begin;
	t_list		*lst;
	t_token		*token;	
	char		str[2];
	int		i;

	begin = NULL;
	str[1] = '\0';
	while (*line)
	{
		token = (t_token*)malloc(sizeof(t_token));
		token->type = literal;
		str[0] = *line;
		token->value = ft_strdup(str);
		i = 0;
		while (g_token_tab[i].value)
		{
			if (g_token_tab[i].value[0] == token->value[0])
				token->type = g_token_tab[i].type;
			i++;
		}
		lst = ft_lstnew((void*)token);
		ft_lstadd_back(&begin, lst);
		line++;
	} return (begin);
}

//double quotes == 22
//single quotes == 27

void		ssingle_quote(t_list **begin, t_list *lst, char *last, char *backsl)
{
	t_token	*token;

	token = (t_token*)((lst)->content);
	if (!*backsl && !*last)
	{
		*last = 27;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (!*backsl && *last == 27)
	{
		*last = 0;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (*backsl || *last == 22)
	{
		if (*backsl)
			*backsl = 0;
		token->type = literal; 	
	}
}

void		ddouble_quote(t_list **begin, t_list *lst, char *last, char *backsl)
{
	t_token	*token;

	token = (t_token*)((lst)->content);
	if (!*backsl && !*last)
	{
		*last = 22;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (!*backsl && *last == 22)
	{
		*last = 0;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (*backsl || *last == 27)
	{
		if (*backsl)
			*backsl = 0;
		token->type = literal; 	
	}
}

void		bbackslash(t_list **begin, t_list *lst, char *last, char *backsl)
{
	t_token *token;

	token = (t_token*)(lst->content);
	if (!*backsl && (!*last || *last == 22))
	{
		*backsl = 1;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (*backsl || *last == 27)
	{
		if (*backsl)
			*backsl = 0;
		token->type = literal;
	}
}

void		solve_quotes(t_list **alst)
{
	t_list	*begin;
	t_list	*lst;
	t_token	*token;
	char	last;
	char	backsl;
	
	begin = *alst;
	lst = *alst;
	last = 0;
	backsl = 0;
	while (lst)
	{
		token = (t_token*)(lst->content);
		if (token->type == single_quote)
			ssingle_quote(&begin, lst, &last, &backsl);	
/*		{
			if (!backsl && (!last))
				// last = 27 + del elem + func_single_quote(&la, &bac)
			else if (backsl || last == 22)
				// single_quote is a literal + (backsl = 0)
		}*/
		else if (token->type == double_quote)
			ddouble_quote(&begin, lst, &last, &backsl);
/*		{
			if (!backsl && !last)
				// last = 22 + del elem + func_double_quote
			else if (backsl || last == 27)
				// double_quote is a literal + (backsl = 0 (if 1))
		}*/
		else if (token->type == backslash)
			bbackslash(&begin, lst, &last, &backsl);
/*		{
			if (!backsl && (!last || last == 22))
				// normal behav, eliminar elemento y literalizar next
			else if (backsl || last == 27)
				// backsl is a literalll + (backsl = 0(if 1))
		}*/
		else if (backsl || last)
		{
			token->type = literal;
			if (backsl)
				backsl = 0;
		}
		lst = lst->next;
	}
	*alst = begin;
}

t_list				*pparse_line(char *line)
{
	t_list	*lst;

	lst = line_to_token_list(line);
	solve_quotes(&lst);
	return (lst);
	
	

	

	//lstiter to solve \, ' and "
	
	// join lst

	//build tree
}


int main(int ac, char **av)
{
	t_list	*lst;
	t_token	*token;
	char *line="echo \\' \"ls | wc outputs; \\n\";ls | wc";
		
	lst = pparse_line(line);
	//ft_lstdelone(&lst, lst, &free_token);

	while (lst)
	{
		token = (t_token*)(lst->content);
		ft_printf("%s <- %d\n", token->value, token->type);
		lst = lst->next;
	}
	return (0);
}
