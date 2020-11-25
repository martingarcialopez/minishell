#include "builtins.h"
#include "tree.h"
#include "libft.h"

// ERROR ERRROR ERRORRR >>>> Revisar la funcion line_to_token_lst, y join // |, ||, &, &&, >, >>, pipe, or y and mal gestionados

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

char				**create_command(t_list **alst, t_list *lst)
{
    t_list	*begin;
    t_token	*token;
    char	**cmd;
    int		i;

    begin = *alst;
    i = 1;
    while (begin != lst)
    {
	i++;
	begin = begin->next;
    }
    cmd = (char**)sec(malloc(sizeof(char*) * (i + 1)));
    while (--i >= 0)
	cmd[i] = NULL;
    i = 0;
    begin = *alst;	
    while (begin != lst)
    {
	token = begin->content;
	if (token->type == literal)
	    cmd[i++] = sec(ft_strdup(token->value));
	begin = begin->next;
    }
    cmd[++i] = NULL;	
    return (cmd);
}

t_tree				*bbuild_tree(t_list **alst)
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
	if ((token->type == pipeline) || (token->type == right_redir)
		|| (token->type == left_redir) || (token->type == double_right_redir))
	{
	    cmd = (char**)sec(malloc(sizeof(char*) * 2));
	    cmd[0] = sec(ft_strdup("op"));
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
    //	if (*sep)
    //		*alst = (*alst)->next;
    return (root);
}

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
	token = (t_token*)sec(malloc(sizeof(t_token)));
	token->type = literal;
	str[0] = *line;
	token->value = sec(ft_strdup(str));
	i = 0;
	while (g_token_tab[i].value)
	{
	    if (ft_strcmp(g_token_tab[i].value, token->value) == 0)
		token->type = g_token_tab[i].type;
	    i++;
	}
	lst = sec(ft_lstnew((void*)token));
	ft_lstadd_back(&begin, lst);
	line++;
    } return (begin);
}

//double quotes == 34
//single quotes == 39

void		ssingle_quote(t_list **begin, t_list *lst, char *last, char *backsl)
{
    t_token	*token;

    token = (t_token*)((lst)->content);
    if (!*backsl && !*last)
    {
	*last = 39;
	ft_lstdelone(begin, lst, &free_token);
    }
    else if (!*backsl && *last == 39)
    {
	*last = 0;
	ft_lstdelone(begin, lst, &free_token);
    }
    else if (*backsl || *last == 34)
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
	*last = 34;
	ft_lstdelone(begin, lst, &free_token);
    }
    else if (!*backsl && *last == 34)
    {
	*last = 0;
	ft_lstdelone(begin, lst, &free_token);
    }
    else if (*backsl || *last == 39)
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
    if (!*backsl && (!*last || *last == 34))
    {
	*backsl = 1;
	ft_lstdelone(begin, lst, &free_token);
    }
    else if (*backsl || *last == 39)
    {
	if (*backsl)
	    *backsl = 0;
	token->type = literal;
    }
}

void		solve_quotes(t_list **alst)
{
    t_list	*lst;
    t_list	*tmp;
    t_token	*token;
    char	last;
    char	backsl;

    lst = *alst;
    last = 0;
    backsl = 0;
    while (lst)
    {
	tmp = lst->next;
	token = (t_token*)(lst->content);
	if (token->type == single_quote)
	    ssingle_quote(alst, lst, &last, &backsl);	
	else if (token->type == double_quote)
	    ddouble_quote(alst, lst, &last, &backsl);
	else if (token->type == backslash)
	    bbackslash(alst, lst, &last, &backsl);
	else if (backsl || last)
	{
	    if (!(last == 34 && token->type == variable))
		token->type = literal;
	    if (backsl)
		backsl = 0;
	}
	lst = tmp;
    }
    if (last)
	parse_error(2, &last, alst); 
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
	    token->value = sec(ft_strjoin(token->value, next_token->value));
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
	if (token->type != literal && token->type != space)
	{
	    i = 0;
	    while (lst && g_token_tab[i].value)
	    {
		if (ft_strcmp(g_token_tab[i].value, token->value) == 0)
		{
		    token->type = g_token_tab[i].type;
		    if (token->type == half_and)
			parse_error(1, token->value, alst);
		    break;
		}
		i++;
	    }
	    if (!g_token_tab[i].value)
	    {
	        parse_error(1, token->value, alst);
		return ;
	    }
	}
	if (lst)
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
    char        *tmp;

    lst = *alst;
    while (lst && lst->next)
    {
	token = (t_token*)lst->content;
	next_token = (t_token*)lst->next->content;
	if (token->type == variable && (next_token->type == status || (next_token->type == literal && ft_strcmp(next_token->value, "\'") != 0)))
	{
	    token->type = literal;	
            tmp = token->value;
	    if (!(retrieve_env_variable(next_token->value, &env_variable)))
		token->value = sec(ft_strdup(""));
	    else
		token->value = env_variable;
            free(tmp);
	    ft_lstdelone(alst, lst->next, &free_token);
	}
	else if (token->type == variable /*&& (next_token->type != literal || ft_strcmp(next_token->value, "\'") == 0)*/)
	    token->type = literal;
	lst = lst->next;
    }	
    if (lst)
    {
	token = (t_token*)lst->content;
	if (token->type == variable)
	    token->type = literal;
    }
}

void				remove_whitespaces(t_list **alst)
{
    t_list	*lst;
    t_list	*tmp;
    t_token	*token;

    lst = *alst;
    while (lst)
    {
	token = (t_token*)lst->content;
	if (token->type == space)
	{
	    tmp = lst->next;
	    ft_lstdelone(alst, lst, &free_token);
	    lst = tmp;
	}
	else
	    lst = lst->next;
    }
}

void				put_lstnext_before_redir(int *redir, t_list **elem, t_list **prev, t_list **begin)
{
    t_list  *elem_prev;
    t_list  *elem_next;
    t_list  *prev_next;

    *redir = 0;
    elem_prev = *elem;
    *elem = (*elem)->next;
    elem_next = (*elem)->next;
    if (*prev == NULL)
    {
	(*elem)->next = *begin;
	*begin = *elem;
    }
    else
    {
	prev_next = (*prev)->next; 
	(*prev)->next = *elem;
	(*elem)->next = prev_next;
    }
    elem_prev->next = elem_next;
}

void				trambolic_redirections(t_list **alst)
{
    t_list	*lst;
    t_list	*prev;
    t_token	*t;
    t_token	*nt;
    int		redir;
    
    lst = *alst;
    prev = NULL;
    redir = 0;
    while (lst && lst->next)
    {
	t = (t_token*)lst->content;
	nt = (t_token*)lst->next->content;
	if (t->type == right_redir || t->type == double_right_redir)
	    redir = 1;
	else if (t->type == semicolon)
	    redir = 0;
	else if (nt->type == right_redir || nt->type == double_right_redir)
	    prev = lst;
	else if (redir && t->type == literal && nt->type == literal)
	{
	    put_lstnext_before_redir(&redir, &lst, &prev, alst);
	    lst = *alst;
	    continue ;
	}
	lst = lst->next;
    }
}

void				swap_list_elements(t_list **link1, t_list **link2, t_list **alst)
{
    t_list	*lst;
    t_list	*l1_prev;
    t_list	*l2_prev;
    t_list	*swap;

    lst = *alst;
    while (lst)
    {
	if (lst->next == *link1)
	    l1_prev = lst;
	else if (lst->next == *link2)
	    l2_prev = lst;
	lst = lst->next;
    }
    swap = (*link1)->next;
    (*link1)->next = (*link2)->next;
    (*link2)->next = swap;
    l1_prev->next = *link2;
    l2_prev->next = *link1;
}

void				redirection_party_trick(t_list **alst)
{
    t_list	*lst;
    t_list	*a;
    t_list	*b;
    t_token	*t;
    int		redir;

    lst = *alst;
    redir = 0;
    a = NULL;
    b = NULL;
    while (lst)
    {
	t = (t_token*)lst->content;
	if (t->type == right_redir || t->type == double_right_redir)
	{
	    a = !redir ? lst->next : a;
	    b = redir ? lst->next : b;
	    redir++;
	}
	lst = lst->next;
    }
    if (a && b)
	swap_list_elements(&a, &b, alst);
}

int                             is_operator(t_token_type type)
{
    if (type == pipeline || type == or || type == and
	    || type == left_redir)
	return (1);
    return (0);
}

void                            check_syntax(t_list **alst)
{
    t_list  *lst;
    t_token *tkn;
    t_token *ntkn;

    lst = *alst;
    while (lst && lst->next)
    {
	tkn = (t_token*)lst->content;
	ntkn = (t_token*)lst->next->content;
	if (is_operator(tkn->type) && lst == *alst)
	{
	    parse_error(1, tkn->value, alst);
	    return ;
	}
	else if (is_operator(tkn->type) && ntkn->type != literal)
	{
	    parse_error(1, tkn->value, alst);
	    return ;
	}
	else if (tkn->type != literal && is_operator(ntkn->type))
	{
	    parse_error(1, tkn->value, alst);
	    return ;
	}
	if (lst)
	    lst = lst->next;
    }
    if (lst)
    {
	tkn = (t_token*)lst->content;
	if (is_operator(tkn->type))
	    parse_error(1, tkn->value, alst);
    }
}

t_list				*pparse_line(char *line)
{
    t_list	*lst;

    lst = line_to_token_list(line);
    solve_quotes(&lst);
    join_token_of_the_same_type(&lst);
    reevaluate_token(&lst);
    //expand_variables(&lst);
    remove_whitespaces(&lst);
    trambolic_redirections(&lst);
    redirection_party_trick(&lst);
//    check_syntax(&lst);

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
