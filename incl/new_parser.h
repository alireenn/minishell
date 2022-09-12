/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:53:14 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/12 15:41:44 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_PARSER_H
# define NEW_PARSER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <libft.h>

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

int			special_issep(char c, char *str);
char		*parse_tree(char *input);
char		**special_split(char *str, char *charset, int *c);

t_tree		make_tree(char *input, int *cmd);
t_tree		null_tree(void);
int			radix(t_tree a);
int			is_null(t_tree a);
t_node_tree	*nodoalb_alloc(int e);
t_tree		create_bin_tree(int infoRadice, t_tree sx, t_tree dx);
/*
**		ft_tree2.c
*/
void		free_tree(t_tree *a);
void		print_tree(t_tree *a);
int			get_tree_size(t_tree a);
int			get_tree_depth(t_tree a);

t_command	**alloc_cmds(int cmd);
int			search_closing(char *input, int c);
char		**split_parser(char *input, int cmd);
int			check_parse(char *parsed);
void		get_redirs(char **splitted, t_command **cmds, int cmd);

#endif