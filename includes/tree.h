/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:21:56 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 17:43:13 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "libft.h"
# include <sys/wait.h>

# define MAJOR_VERSION 1
# define MINOR_VERSION 4

# ifndef SYNTAX_ERROR
#  define SYNTAX_ERROR 1
# endif

# ifndef EXIT_ERROR
#  define EXIT_ERROR 2
# endif

typedef enum	e_token_type
{
	literal,
	separator,
	and,
	half_and,
	pipeline,
	semicolon,
	left_redir,
	right_redir,
	double_right_redir,
	or,
	single_quote,
	double_quote,
	backslash,
	variable,
	status,
	space,
	eof
}				t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
}				t_token;

typedef struct	s_tree
{
	t_token_type	type;
	char			**data;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

void			print_ascii_tree(t_tree *tree);

t_tree			*ft_newtree(t_token_type type, char **cmd);

void			ft_treeadd_root(t_tree **rtree, t_tree *new);

int				ft_add_leaf_dfs(t_tree **rtree, t_tree *new);

void			print_dfs_tree(t_tree *node);

t_list			*parse_line(char *str);

t_list			*pparse_line(char *line);

t_tree			*bbuild_tree(t_list *lst);

void			display_ascii_art(void);

int				exec_commands(t_tree *tree);

int				call_system_function(char **args);

char			**env_to_vect(void);

int				retrieve_env_variable(char *name, char **value);

char			*solve_cmd_path(char **args);

int				redirection(t_tree *tree);

char			*solve_home(char *arg);

void			free_tab(char **tab);

void			free_tree(t_tree *node);

void			free_token(void *tkn);

void			signal_handler(int sigid);

void			parse_error(int n, void *value, t_list **alst);

char			*error_retrieving_env_variable(char *var);

int				error(char *err);

void			expand_variables(t_list **alst);

void			print_token_lst(t_list *alst);

void			join_token_of_the_same_type(t_list **alst);

void			solve_quotes(t_list **alst);

void			trambolic_redirections(t_list **alst);

void			redirection_party_trick(t_list **alst);

void			remove_whitespaces(t_list **alst);

void			check_syntax(t_list **alst);

void			join_quotes(t_list **alst);

int				check_path_status(char *path);

char			*error_retrieving_env_variable(char *var);

char			*command_not_found(char **tab, char *str, char *cmd);

char			*free_tab_and_return_path(char **tab, char *abs_path);

char			*is_a_directory(char *path);

void			join_dollar(t_list **alst);

void			new_prompt(void);

void			split_lst_by_semicolon(t_list **alst, t_list **next, char *sep);

int				exec_single_command(char *line);

int				manage_flags(int ac, char **av, char **envp);

void			solve_command(char *line);

int				open_error(char *err);

int				error_fork_failed(void);

#endif
