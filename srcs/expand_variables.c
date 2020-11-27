/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:00:21 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 19:25:37 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

void				join_adjacent_elems(t_list **al, t_list *elem)
{
	t_list	*lst;
	t_token	*token;
	t_token	*next_token;
	char	*tmp;

	lst = *al;
	while (lst && lst->next)
	{
		token = (t_token*)lst->content;
		next_token = (t_token*)lst->next->content;
		if (lst->next == elem && token->type == literal)
		{
		    tmp = token->value;
		    token->value = ft_strjoin(token->value, next_token->value);
		    free(tmp);
		    ft_lstdelone(al, lst->next, &free_token);
		    elem = lst;
		    continue ;
		}
		if (lst == elem && next_token->type == literal)
		{
		    tmp = token->value;
		    token->value = ft_strjoin(token->value, next_token->value);
		    free(tmp);
		    ft_lstdelone(al, lst->next, &free_token);
		    break ;
		}
		lst = lst->next;
	}
}

void				eexpand_variables(t_list **alst)
{
	t_list	*lst;
	t_token	*token;
	t_token	*next_token;
	char	*env_variable;
	char	*tmp;

	lst = *alst;
	while (lst && lst->next)
	{
		token = (t_token*)lst->content;
		next_token = (t_token*)lst->next->content;
		if (token->type == variable && (next_token->type == literal))
		{
			token->type = literal;
			tmp = token->value;
			if (!(retrieve_env_variable(next_token->value, &env_variable)))
				token->value = sec(ft_strdup(""));
			else
				token->value = env_variable;
			free(tmp);
			ft_lstdelone(alst, lst->next, &free_token);
			join_adjacent_elems(alst, lst);
			lst = *alst;
		}
		else if (token->type == variable)
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

int			    solve_variables(char *str, t_list **alst)
{
    t_list  *node;
    char    *variable;
    char    *value;
    int	    len;
    int	    i;
    int	    j;

    variable = sec(malloc(sizeof(char) * ft_strlen(str)));
    len = 0;
    i =  0;
    while (str[i])
    {
	if (str[i++] == '$')
	{
	    j = 0;
	    while (str[i] && str[i] != 39 && str[i] != 34
			&& str[i] != '=' && str[i] != '$')
		variable[j++] = str[i++];
	    variable[j] = '\0';
	    if (ft_strlen(variable) == 0)
		value = sec(ft_strdup("$"));
	    else if (!(retrieve_env_variable(variable, &value)))
		value = sec(ft_strdup(""));
	    node = ft_lstnew(value);
	    ft_lstadd_back(alst, node);
	    len += ft_strlen(value);
	}
	len++;
    }
    free(variable);
    return (len > 0 ? len : 1);
}

char			    *substitude_variables(char *str)
{
    t_list  *lst;
    t_list  *begin;
    char    *literal;
    int	    len;
    int	    i;
    int	    j;

    lst = NULL;
    len = solve_variables(str, &lst);
    begin = lst;
    literal = sec(malloc(sizeof(char) * len));
    i = 0;
    j = 0;
    while (str[i])
    {
	if (str[i] != '$')
	    literal[j++] = str[i++];
	else
	{
	    i++;
	    literal[j] = '\0';
	    ft_strcat(literal, lst->content);
	    j += ft_strlen(lst->content);
	    lst = lst->next;
	    while (str[i] && str[i] != 39 && str[i] != 34
			    && str[i] != '=' && str[i] != '$')
		i++;
	}
    }
    literal[j] = '\0';
//    ft_printf("literal is %s\n", literal);
    ft_lstclear(&begin, &free);
    return (literal);
}

void				expand_variables(t_list **alst)
{
	t_list	*lst;
	t_token	*token;
	char	*tmp;

	lst = *alst;
	while (lst)
	{
	    token = (t_token*)lst->content; 
	    if (token->type == variable)
	    {
		token->type = literal;
		tmp = token->value;
		token->value = substitude_variables(token->value);
		free(tmp);
	    }
	    lst = lst->next;
	}
}
