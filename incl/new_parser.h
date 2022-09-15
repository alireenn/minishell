/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:53:14 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/15 18:32:21 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_PARSER_H
# define NEW_PARSER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "libft.h"

typedef struct s_env {
	char			*name_var;
	char			*arg_var;
	struct s_env	*next;
}	t_env;

typedef struct s_command {
	char	*com;
	char	*arg;
	int		red[2];
	int		fd_red[2];
	int		res;
}	t_command;

typedef struct s_node_tree {
	int					info;
	struct s_node_tree	*right;
	struct s_node_tree	*left;
}	t_node_tree;

typedef t_node_tree*	t_tree;

typedef struct s_mini {
	t_env		*env;
	t_env		*secret;
	t_tree		tree;
	t_command	**commands;
	int			cmd;
	int			exit;
	char		*pwd;
	int			last;
	int			res;
	int			save_out;
	int			save_in;
}	t_mini;

/*
** 			NEW_PARSER 
*/
//		FT_TREE.C
t_tree		null_tree(void);
int			radix(t_tree a);
int			is_null(t_tree a);
t_node_tree	*nodoalb_alloc(int e);
t_tree		create_bin_tree(int infoRadice, t_tree sx, t_tree dx);
//		FT_TREE2.C
void		free_tree(t_tree *a);
void		print_tree(t_tree *a);
int			get_tree_size(t_tree a);
int			get_tree_depth(t_tree a);
void		print_tree_rec(t_tree a);
//		PARSE_TREE.C
char		*parse_tree(char *input);
int			check_parse(char *parsed);
t_tree		make_tree(char *input, int *cmd);
int			search_closing(char *input, int c);
t_tree		get_next_tree(char *input, int *ind, int *cmd);
char		*ft_strdup_from_to(char *input, int start, int end);
// 		SPECIAL_SPLIT.C
int			special_issep(char c, char *str);
int			special_strlen(char *str, char *charset);
int			special_strcount(char *str, char *charset);
char		**special_split(char *str, char *charset, int *c);
int			special_putstr(char *str, char *charset, char *matrix);
//		SPLIT.C
int			is_sep(char c, char *str);
int			strlen_parser(char *input);
int			putstr_parser(char *input, int len, int offset, char *matrix);
char		**split_parser(char *input, int cmd);
/*
** 			COMMANDS
*/
//		COMMANDS.C
t_command	**alloc_cmds(int cmd);
//		REDIRECTION.C
void		get_redirs(char **s, t_command **cmds, int cmd);
void		replace(char **tbr, int from, int to, char *rep);
char		*ft_strdup_from_to(char *input, int start, int end);
void		emily(int n);
// init.c
void		init_env(t_mini *mini, char **env);
void		init_secret_env(t_mini *mini);
t_mini		*init_mini(char **envp);
// utils.c
void		split_at(char *input, t_env *env, char c);
t_env		*copy_env(t_mini *mini, int *n);
//list.c
t_env		*create_elem(char *elem_name, char *elem_arg);
void		add_elem(t_env **list, char *elem_name, char *elem_arg);
void		add_elem_ord(t_env **list, char *elem_name, char *elem_arg);
void		delete_elem(t_env **list, t_env *elem);
void		change_var(t_env *env, char *name, char *arg);
#endif
