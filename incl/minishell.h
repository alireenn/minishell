/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:36:29 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/05 13:38:45 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
	pid_t		pipe_pid1;
	char		*pid;
	char		*pwd;
	int			cmd;
	int			exit;
	int			last;
	int			res;
	int			save_out;
	int			save_in;
}	t_mini;

int			free_mini(t_mini *mini);
/*
**		BUILDIN
*/
//		cd.c
void		ft_cd_supp2(t_mini *mini, t_command *com);
void		ft_cd(t_mini *mini, char *arg, t_command *com);
void		ft_cd_supp(char *tmp, t_mini *mini, t_command *com, char *arg);
//		env.c
void		free_tmp(t_env *tmp);
char		**trasformation(t_env *env);
void		ft_env(t_env *env, t_command *cmd);
//		env2.c
int			search(t_env *env, char *name);
void		ft_export_supp(t_mini *mini, t_env *tmp);
void		ft_unset(t_mini *mini, char *name, t_command *cmd);
void		unset_help(t_command *cmd, t_mini *mini);
//		export.c
void		export_unset(t_mini *mini, t_command *cmd);
void		ft_print_export(t_env *env, t_command *cmd);
void		ft_export(t_mini *mini, char *str, t_command *cmd);
void		ft_export_replace(t_mini *mini, t_env *tmp, t_command *cmd);
void		export_error(t_env *tmp, t_mini *mini, t_command *cmd, int flag);
//		some_buildin.c
void		ft_pwd(t_command *cmd);
void		ft_exit(t_mini *mini, t_command *com);
//		echo.c
int			check_flag_echo(t_command *com);
void		ft_echo(char *str, t_command *com);
int			flag_echo_help(t_command *cmd, int i);
/*
** 			COMMANDS
*/
// 		commands_utils.c
char		**get_path(t_mini *mini);
int			is_valid_path(char *filename);
void		make_cmd_helper(t_command *cmd, t_mini *mini);
char		*check_path(char *filename, char **path, int i);
void		other_command_helper(t_mini *mini, t_command *cmd);
//		commands.c
t_command	**alloc_cmds(int cmd);
void		other_command(t_command *cmd, t_mini *mini);
void		get_cmds(t_command **cmds, int cmd, char **input);
void		get_cmd_simple(t_command **cmds, char **input, int i, int j);
//		execute.c
int			here_doc(char *end);
char		**get_argv(char *com, char *arg);
void		make_cmd(t_command *cmd, t_mini *mini);
char		*get_filename(t_mini *mini, char *filename);
int			execute(t_tree a, t_command **cmds, t_mini *mini);
//		expand.c
int			check_env_var(char *var);
void		expand(char **s, t_mini *mini);
int			get_len_var(char **s, int i, int j);
int			expand_helper(char **s, int i, int j, t_mini *mini);
int			expand_helper2(char **s, t_mini *mini, int j, int len);
//		ls_fake
char		*ft_pwd_ft(void);
void		remove_quotes_mat(char **matrix);
void		order_mat(char **matrix, int size);
char		*join_mat(char **matrix, int flag);
int			troyella(char **split, char *to_find, char *entry);
//		wildcats.c
char		*what_team(char *filename, char *to_find);
void		what_time_is_it(char **ret, char *to_find);
char		*playmaker(char *to_find, char **split, DIR *dir);
int			wild_cats(char *entry, char **split, char *to_find);
//		mod_split
char		**mod_split(char *str, char *charset, char *avoid);
int			mod_helper(char *str, int i, char *avoid, int open);
int			mod_strcount(char *str, char *charset, char *avoid);
int			mod_putstr(char *str, char *charset, char *matrix, char *avoid);
int			mod_putstr_aux(char *str, char *charset, char *avoid, char *matrix);
//		pid.c
void		my_pid(t_mini *mini);
char		*get_shlvl(t_mini *mini);
void		my_child_get_pid(t_mini *mini, int *fd);
char		*ft_strjoin_3(const char *s1, char *s2, const char *s3);
//		pipe.c
t_tree		essential_pipe(char *input, int *ind, int *cmd);
int			execute_pipe(t_tree a, t_command **cmds, t_mini *mini);
int			execute_pipe2(t_tree a, t_command **cmds, t_mini *mini, int fd[2]);
//		quotes.c
char		*remove_quotes_str(char *str);
//		redirection.c
char		*here_doc_helper(int *fd, char *tmp);
char		*get_file_io(char **s, int r, int j, int *type);
void		get_redirs(char **s, t_command **cmds, int cmd, t_mini *mini);
int			get_red_io(t_command *cmd, char *filename, int type, t_mini *mini);
void		get_redirs_type(char *file, t_mini *mini, t_command *cmd, int type);
//		signal.c
void		ft_sig(void);
void		sig_handle(int sig);
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
//		parse_tree_supp.c
int			check_parse(char *parsed);
int			check_parenthesis(char *input);
int			check_redirs(int i, char *parsed);
char		*parse_tree_helper(char *input, char *ret);
void		put_symbols(char *in, char *ret, int *i, int *j);
//		parse_tree.c
char		*parse_tree(char *input);
t_tree		make_tree(char *input, int *cmd, int pipe);
int			search_closing(char *input, int c, char c1, char c2);
t_tree		get_next_tree(char *input, int *ind, int *cmd, int pipe);
char		*ft_strdup_from_to(char *input, int start, int end);
// 		special_split.c
int			special_strlen(char *str, char *charset);
int			special_strcount(char *str, char *charset);
char		**special_split(char *str, char *charset, int *c);
int			special_putstr(char *str, char *charset, char *matrix);
//		split.c
int			is_sep(char c, char *str);
int			strlen_parser(char *input);
int			check_syntax(char *in, int i);
char		**split_parser(char *input, int cmd);
int			putstr_parser(char *input, int len, int offset, char *matrix);
/*
**		UTILS
*/
//		free.c
void		free_env(t_env *env);
void		free_matrix_no_rows(char **matrix);
void		free_matrix(char **matrix, int rows);
void		free_cmds(t_command	**cmds, int cmd);
void		free_execve(char *filename, char **argv, char **envp);
// 		free_2.c
int			free_mini(t_mini *mini);
void		free_subshell(t_mini *mini2, char **envp2, char *new_cmd);
// 		init.c
t_mini		*init_mini(char **envp);
void		init_secret_env(t_mini *mini);
void		init_env(t_mini *mini, char **env);
//		list_utils.c
int			add_elem_ord_help(t_env *it, char *elem_name);
int			add_elem_ord_norme(t_env **it, char *elem_name);
//		list.c
void		delete_elem(t_env **list, t_env *elem);
t_env		*create_elem(char *elem_name, char *elem_arg);
void		change_var(t_env *env, char *name, char *arg);
void		add_elem(t_env **list, char *elem_name, char *elem_arg);
void		add_elem_ord(t_env **list, char *elem_name, char *elem_arg);
//		process_input.c
int			incomplete_cmd(char *input);
char		*get_other_input(char *input);
char		*our_prompt(int res, t_mini *mini);
void		process_input(t_mini *mini, char *input);
void		process_input_aux(t_mini *mini, char *input);
//		strings.c
int			equal_strings(char *com, char *exec);
char		*ft_join_char(char *s1, char *s2, char c);
void		replace(char **tbr, int from, int to, char *rep);
int			mod_strlen(char *str, char *charset, char *avoid);
char		*get_strip_str(char *input, int from, int to, int flag);
//		env_utils.c
void		change_fd(t_command *cmd);
t_env		*copy_env(t_mini *mini, int *n);
t_env		*ft_search_var(t_env *env, char *name);
void		split_at(char *input, t_env *env, char c);
void		back_to_standard(t_command *cmd, t_mini *mini);
//		debug.c
void		emily(int n);
void		print_mat(char **mat);
void		print_cmds(t_command **cmds, int cmd);
#endif
