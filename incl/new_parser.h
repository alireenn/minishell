/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:36:29 by anovelli          #+#    #+#             */
/*   Updated: 2022/10/19 10:56:27 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef NEW_PARSER_H
# define NEW_PARSER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../lib/libft/libft.h"
# include "../lib/printf_fd/ft_printf.h"

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

void		process_input(t_mini *mini, char *input);
/*
**		BUILDIN
*/
//		cd.c
void		ft_cd_supp2(t_mini *mini, t_command *com);
void		ft_cd(t_mini *mini, char *arg, t_command *com);
void		ft_cd_supp(char *tmp, t_mini *mini, t_command *com, char *arg);
//		env.c
char		**trasformation(t_env *env);
void		init_env(t_mini *mini, char **env);
void		ft_env(t_env *env, t_command *cmd);
void		ft_print_export(t_env *env, t_command *cmd);
void		ft_export(t_mini *mini, char *str, t_command *cmd);
//		env2.c
int			search(t_env *env, char *name);
void		ft_export_supp(t_mini *mini, t_env *tmp);
void		ft_unset(t_mini *mini, char *name, t_command *cmd);
//		some_buildin.c
int			check_par(char *str);
void		ft_pwd(t_command *cmd);
int			check_flag_echo(t_command *cmd);
void		ft_echo(char *str, t_command *com);
void		ft_exit(t_mini *mini, t_command *com);
/*
** 			COMMANDS
*/
//		mod_split
int		mod_strlen(char *str, char *charset, char *avoid);
char	**mod_split(char *str, char *charset, char *avoid);
int		mod_helper(char *str, int i, char *avoid, int open);
int		mod_strcount(char *str, char *charset, char *avoid);
int		mod_putstr(char *str, char *charset, char *matrix, char *avoid);
//		expand.c
void		expand(char **s, t_mini *mini);
int			get_len_var(char **s, int i, int j);
int			expand_helper(char **s, int i, int j, t_mini *mini);
int			expand_helper2(char **s, t_mini *mini, int j, int len);
//		commands.c
t_command	**alloc_cmds(int cmd);
void		get_cmds(t_command **cmds, int cmd, char **input);
void		get_cmd_simple(t_command **cmds, char **input, int i, int j);
//		execute.c
char		**get_argv(char *com, char *arg);
void		make_cmd(t_command *cmd, t_mini *mini);
char		*get_filename(t_mini *mini, char *filename);
void		other_command(t_command *cmd, t_mini *mini);
int			execute(t_tree a, t_command **cmds, t_mini *mini);
// 		commands_utils.c
char		**get_path(t_mini *mini);
int			is_valid_path(char *filename);
void		make_cmd_helper(t_command *cmd, t_mini *mini);
char		*check_path(char *filename, char **path, int i);
void		other_command_helper(t_mini *mini, t_command *cmd);
//		commands_utils2.c
void		remove_quotes_arg(t_command *cmd);
void		remove_quotes_com(t_command *cmd);
//		redirection.c
int			here_doc(char *end);
char		*here_doc_helper(int *fd, char *tmp);
char		*get_file_io(char **s, int r, int j, int *type);
void		get_redirs(char **s, t_command **cmds, int cmd, t_mini *mini);
//		signal.c
void		quit(int sig);
void		received(int sig);
/*
** 			NEW_PARSER 
*/
//		ft_tree.c
t_tree		null_tree(void);
int			radix(t_tree a);
int			is_null(t_tree a);
t_node_tree	*nodoalb_alloc(int e);
t_tree		create_bin_tree(int infoRadice, t_tree sx, t_tree dx);
//		ft_tree2.c
void		free_tree(t_tree *a);
void		print_tree(t_tree *a);
int			get_tree_size(t_tree a);
int			get_tree_depth(t_tree a);
void		print_tree_rec(t_tree a);
//		parse_tree.c
char		*parse_tree(char *input);
t_tree		make_tree(char *input, int *cmd);
int			search_closing(char *input, int c, char c1, char c2);
t_tree		get_next_tree(char *input, int *ind, int *cmd);
char		*ft_strdup_from_to(char *input, int start, int end);
//		parse_tree_supp.c
int			check_parse(char *parsed);
char		*parse_tree_helper(char *input, char *ret);
// 		special_split.c
int			is_sep(char c, char *str);
int			special_strlen(char *str, char *charset);
int			special_strcount(char *str, char *charset);
char		**special_split(char *str, char *charset, int *c);
int			special_putstr(char *str, char *charset, char *matrix);
//		split.c
int			is_sep(char c, char *str);
int			strlen_parser(char *input);
char		**split_parser(char *input, int cmd);
int			putstr_parser(char *input, int len, int offset, char *matrix);
/*
**		UTILS
*/
//		strings.c
char		*remove_quotes_str(char *str);
int			equal_strings(char *com, char *exec);
char		*ft_join_char(char *s1, char *s2, char c);
char		*get_strip_str(char *input, int from, int to);
void		replace(char **tbr, int from, int to, char *rep);
// 		init.c
t_mini		*init_mini(char **envp);
void		init_secret_env(t_mini *mini);
void		init_env(t_mini *mini, char **env);
//		utils.c
void		change_fd(t_command *cmd);
t_env		*copy_env(t_mini *mini, int *n);
t_env		*ft_search_var(t_env *env, char *name);
void		split_at(char *input, t_env *env, char c);
void		back_to_standard(t_command *cmd, t_mini *mini);
//		list.c
void		delete_elem(t_env **list, t_env *elem);
t_env		*create_elem(char *elem_name, char *elem_arg);
void		change_var(t_env *env, char *name, char *arg);
void		add_elem(t_env **list, char *elem_name, char *elem_arg);
void		add_elem_ord(t_env **list, char *elem_name, char *elem_arg);
//		free.c
void		free_env(t_env *env);
void		free_mini(t_mini *mini);
void		free_matrix_no_rows(char **matrix);
void		free_matrix(char **matrix, int rows);
void		free_cmds(t_command	**cmds, int cmd);
void		free_execve(char *filename, char **argv, char **envp);
//		debug.c
void		emily(int n);
void		print_mat(char **mat);
void		print_cmds(t_command **cmds, int cmd);
#endif
