#include "builtins.h"
#include "tree.h"
#include "libft.h"

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
