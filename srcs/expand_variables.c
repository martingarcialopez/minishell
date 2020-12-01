/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:00:21 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 12:47:20 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"

int					put_variable_to_list(int *i, char *variable,
													char *str, t_list **alst)
{
	t_list	*node;
	char	*value;
	int		j;

	j = 0;
	while (str[*i] && str[*i] != 39 && str[*i] != 34
			&& str[*i] != '=' && str[*i] != '$')
		variable[j++] = str[(*i)++];
	variable[j] = '\0';
	if (ft_strlen(variable) == 0)
		value = sec(ft_strdup("$"));
	else if (!(retrieve_env_variable(variable, &value)))
		value = sec(ft_strdup(""));
	node = ft_lstnew(value);
	ft_lstadd_back(alst, node);
	return (ft_strlen(value));
}

int					solve_variables(char *str, t_list **alst)
{
	char	*variable;
	int		len;
	int		i;

	variable = sec(malloc(sizeof(char) * ft_strlen(str)));
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
			len += put_variable_to_list(&i, variable, str, alst);
		len++;
	}
	free(variable);
	return (len > 0 ? len : 1);
}

void				replace_variable_name_per_value(int *i, int *j,
												char **literal, t_list **lst)
{
	(*i)++;
	(*literal)[*j] = '\0';
	ft_strcat(*literal, (*lst)->content);
	*j += ft_strlen((*lst)->content);
	*lst = (*lst)->next;
}

char				*substitude_variables(char *str, int i, int j)
{
	t_list	*lst;
	t_list	*begin;
	char	*literal;
	int		len;

	lst = NULL;
	len = solve_variables(str, &lst);
	begin = lst;
	literal = sec(malloc(sizeof(char) * len));
	while (str[i])
	{
		if (str[i] != '$')
			literal[j++] = str[i++];
		else
		{
			replace_variable_name_per_value(&i, &j, &literal, &lst);
			while (str[i] && str[i] != 39 && str[i] != 34
					&& str[i] != '=' && str[i] != '$')
				i++;
		}
	}
	literal[j] = '\0';
	ft_lstclear(&begin, &free);
	return (literal);
}

void				expand_variables(t_list **alst)
{
	t_list	*lst;
	t_token	*token;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lst = *alst;
	while (lst)
	{
		token = (t_token*)lst->content;
		if (token->type == variable)
		{
			token->type = literal;
			tmp = token->value;
			token->value = substitude_variables(token->value, i, j);
			free(tmp);
		}
		lst = lst->next;
	}
}
