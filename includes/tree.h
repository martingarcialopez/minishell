/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:21:56 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 20:59:11 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TREE_H_
# define _TREE_H_

# include "libft.h"
# include <sys/wait.h>

# define MAJOR_VERSION 1
# define MINOR_VERSION 3

typedef enum		e_token_type
{
	literal,//0
	separator,//1
	and,//2
	half_and,//3
	pipeline,//4
	semicolon,//5
	left_redir,//6
	right_redir,//7
	double_right_redir,//8
	or,//9
	single_quote,//10
	double_quote,//11
	backslash,//12
	variable,//13
	status,//14
	space,//15
	eof//16
}			t_token_type;

typedef struct		s_token
{
	char		*value;
	t_token_type	type;
	
}			t_token;

typedef struct		s_tree
{
	t_token_type	type;
	char		**data;
	struct s_tree	*left;
	struct s_tree	*right;
}			t_tree;

void			print_ascii_tree(t_tree *tree);

t_tree			*ft_newtree(t_token_type type, char **cmd);

void			ft_treeadd_root(t_tree **rtree, t_tree *new);

int			ft_add_leaf_dfs(t_tree **rtree, t_tree *new);

void			print_dfs_tree(t_tree *node);

t_list			*parse_line(char *str);

t_list			*pparse_line(char *line);

t_tree			*bbuild_tree(t_list **alst);

void			display_ascii_art(void);

int			exec_commands(t_tree *tree);

int			call_system_function(char **args);

char			**env_to_vect(void);

int			retrieve_env_variable(char *name, char **value);

char			*solve_cmd_path(char **args);

int			redirection(t_tree *tree);

char			*solve_home(char *arg);

void			free_tab(char **tab);

void			free_tree(t_tree *node);

void			free_token(void *tkn);

void			signal_handler(int sigid);

void			parse_error(int n, void *value, t_list **alst);

char			*error_retrieving_env_variable(char *var);

int			error(char *err);

void			expand_variables(t_list **alst);

void			print_token_lst(t_list *alst);

void			join_token_of_the_same_type(t_list **alst);

void			solve_quotes(t_list **alst);

void			trambolic_redirections(t_list **alst);

void			redirection_party_trick(t_list **alst);

void			remove_whitespaces(t_list **alst);

void			check_syntax(t_list **alst);

void			join_quotes(t_list **alst);

int			check_path_status(char *path);

char			*error_retrieving_env_variable(char *var);

char			*command_not_found(char **tab, char *str, char *cmd);

char			*free_tab_and_return_path(char **tab, char *abs_path);

char			*is_a_directory(char *path);

void			join_dollar(t_list **alst);

#endif
