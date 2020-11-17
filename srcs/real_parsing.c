#include "builtins.h"
#include "tree.h"
#include "libft.h"

// ERROR ERRROR ERRORRR >>>> Revisar la funcion line_to_token_lst, y join
// |, ||, &, &&, >, >>, pipe, or y and mal gestionados

static t_token			g_token_tab[] = {
	{"|", pipeline},
	{"<", left_redir},
	{">", right_redir},
	{";", semicolon},
	{"&", half_and},
	{"\'", single_quote},
	{"\"", double_quote},
	{"\\", backslash},
	{" ", space},
	{"$", variable},
	{"?", status},
	{">>", double_right_redir},
	{"&&", and},
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

//free strjoin
char				**create_command(t_list **alst, t_list *lst)
{
	t_list	*begin;
	t_list	*tmp;
	t_token	*token;
	char	**cmd;
	int	i;
	

	begin = *alst;
	i = 1;
	while (begin != lst)
	{
		if (((t_token*)begin->content)->type == space)
			i++;
		begin = begin->next;
	}
	cmd = (char**)malloc(sizeof(char*) * (i + 1));
	while (--i >= 0)
		cmd[i] = NULL;
	i = 0;
	begin = *alst;	
	while (begin != lst)
	{
		token = begin->content;
		if (token->type == space)
		{
			i++;
			begin = begin->next;
			continue;
		}
		if (cmd[i] == NULL)
			cmd[i] = ft_strdup(token->value);
		else
			cmd[i] = ft_strjoin(cmd[i], token->value);

		tmp = begin->next;
		ft_lstdelone(alst, begin, &free_token);
		begin = tmp;	
	}
	

	i++;
	cmd[i] = NULL;	
	i = 0;
//	while (cmd[i])
//		ft_printf("cmd[%d] is %s\n", i, cmd[i++]);
	return (cmd);
}

t_tree				*bbuild_tree(t_list **alst, char *sep)
{
	t_list		*lst;
	t_token		*token;
	char		**cmd;

	t_tree		*root;
	t_tree		*tree;

	root = NULL;
	lst = *alst;
	while (lst)
	{
		token = (t_token*)(lst->content);	
		if (token->type == semicolon || token->type == and || token->type == or)
		{
			if (token->type == semicolon)
				*sep = ';';
			else if (token->type == and)
				*sep = '&';
			else if (token->type == or)
				*sep = '|';
			break;
		}

		if ((token->type == pipeline) || (token->type == right_redir)
			|| (token->type == left_redir) || (token->type == double_right_redir))
		{
			cmd = (char**)malloc(sizeof(char*) * 2);
			cmd[0] = ft_strdup("op");
			cmd[1] = NULL;
			tree = ft_newtree(token->type, cmd);
			ft_treeadd_root(&root, tree);

			cmd = create_command(alst, lst);
			tree = ft_newtree(literal, cmd);
			ft_add_leaf_dfs(&root, tree);
			*alst = lst->next;
		}
		lst = lst->next;
	}
	cmd = create_command(alst, lst);
	tree = ft_newtree(literal, cmd);
	if (!root)
		ft_treeadd_root(&root, tree);
	else
		ft_add_leaf_dfs(&root, tree);
	if (*sep)
		*alst = (*alst)->next;
	return (root);
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
			if (ft_strcmp(g_token_tab[i].value, token->value) == 0)
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
		else if (token->type == double_quote)
			ddouble_quote(&begin, lst, &last, &backsl);
		else if (token->type == backslash)
			bbackslash(&begin, lst, &last, &backsl);
		else if (backsl || last)
		{
			if (!(last == 22 && token->type == variable))
				token->type = literal;
			if (backsl)
				backsl = 0;
		}
		lst = lst->next;
	}
	*alst = begin;
}


void				join_token_of_the_same_type(t_list **alst)
{
	t_list	**begin;
	t_list	*lst;
	t_token	*token;
	t_token	*next_token;
	char	*tmp;

	begin = alst;
	lst = *alst;
	while (lst && lst->next)
	{
		token = (t_token*)(lst->content);
		next_token = (t_token*)(lst->next->content);
		if (token->type == next_token->type)
		{
			tmp = token->value;
			token->value = ft_strjoin(token->value, next_token->value);
			free(tmp);
			ft_lstdelone(begin, lst->next, &free_token);
		}
		else
			lst = lst->next;
	}
}

void				reevaluate_token(t_list **alst)
{
	t_list	*lst;
	t_token	*token;
	int	i;

	lst = *alst;
	while (lst)
	{
		token = (t_token*)(lst->content);
		if (token->type != literal)
		{
			i = 0;
			while (g_token_tab[i].value)
			{
				if (ft_strcmp(g_token_tab[i].value, token->value) == 0)
				{
					token->type = g_token_tab[i].type;
					break;
				}
				i++;
				if (!g_token_tab[i].value)
				{
					ft_printf("vsh: parse error near `%c\'\n", token->value[0]);
					*alst = NULL;
					return ;
				}
			}
		}
		lst = lst->next;
	}
	
}

//	David. Time to work. Do your thing Go Go Goooooo
void				expand_variables(t_list **alst)
{
	t_list	*lst;
	t_token	*token;
	t_token	*next_token;
	char	*env_variable;

	lst = *alst;
	while (lst && lst->next)
	{
		token = (t_token*)lst->content;
		next_token = (t_token*)lst->next->content;
		if (token->type == variable)
		{
			token->type = literal;	
			if (!(retrieve_env_variable(next_token->value, &env_variable)))
				token->value = ft_strdup("");
			else
				token->value = env_variable;
			ft_lstdelone(alst, lst->next, &free_token);
		}
		lst = lst->next;
	}	
}

// mas waitespaises tiene que removear esto eh, que las cabrillas tambien se cogen
void				remove_whitespaces(t_list **alst)
{
	t_list	*lst;
	t_token	*token;
	t_token *next_token;

	lst = *alst;
	while (lst && lst->next)
	{
		token = (t_token*)lst->content;
		next_token = (t_token*)lst->next->content;
		if ((token->type == space && next_token->type != literal)
			|| (token->type == space && *alst == lst))
			ft_lstdelone(alst, lst, &free_token);
		else if (token->type != literal && next_token->type == space)
			ft_lstdelone(alst, lst->next, &free_token);
		lst = lst->next;
	}
}

t_list				*pparse_line(char *line)
{
	t_list	*lst;
	t_tree	*tree;
	int	ret;
	char	sep;

	lst = line_to_token_list(line);
	solve_quotes(&lst);
	join_token_of_the_same_type(&lst);
	reevaluate_token(&lst);
	expand_variables(&lst);
	remove_whitespaces(&lst);
	return (lst);
}
/*
int main(int ac, char **av)
{
	t_list	*lst;
	t_token	*token;
	char *line="echo \\' \"ls | wc outputs; \\n\";ls | wc";
		
	lst = pparse_line(av[1]);
	//ft_lstdelone(&lst, lst, &free_token);

	while (lst)
	{
		token = (t_token*)(lst->content);
		ft_printf("%s <- %d\n", token->value, token->type);
		lst = lst->next;
	}
//	ft_lstclear(&lst, &free_token);
	while (1)
		;
	return (0);
}*/
