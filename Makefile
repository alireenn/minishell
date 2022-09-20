NAME			= minishell

# libraries
LIB_DIR			= ./lib

LIBFT_DIR		= $(LIB_DIR)/libft
LIBFT_A			= $(LIBFT_DIR)/libft.a

PRINTFFD_DIR	= $(LIB_DIR)/printf_fd
PRINTFFD_A		= $(PRINTFFD_DIR)/printf_fd.a

LIB_A	= $(LIBFT_A) $(PRINTFFD_A)

HEAD_DIR		= ./incl

MAIN			= minishell.c

NEW_PARSER_FILES=				\
		ft_tree.c				\
		ft_tree2.c				\
		parse_tree.c			\
		special_split.c			\
		parse_tree_supp.c 		\
		split.c 				\

NEW_PARSER		= $(addprefix new_parser/, $(NEW_PARSER_FILES))

COMMANDS_FILES=					\
		commands.c				\
		execute.c				\
		redirections.c 			\

COMMANDS		= $(addprefix commands/, $(COMMANDS_FILES))

BUILDIN_FILES	=				\
		cd.c					\
		env.c					\
		env2.c					\
		some_buildin.c			\

BUILDIN			= $(addprefix buildin/, $(BUILDIN_FILES))

# SIGNAL_FILES	= signal.c		\

# SIGNAL			= $(addprefix signal/, $(SIGNAL_FILES))

UTILS_FILES		=				\
		strings.c				\
		list.c					\
		utils.c					\
		init.c					\
		free.c					\
		debugging.c				\

UTILS			= $(addprefix utils/, $(UTILS_FILES))

SRCS_DIR		= ./srcs
SRCS			=								\
		$(addprefix $(SRCS_DIR)/,$(NEW_PARSER))	\
		$(addprefix $(SRCS_DIR)/,$(COMMANDS))	\
		$(addprefix $(SRCS_DIR)/,$(UTILS))		\
		$(addprefix $(SRCS_DIR)/,$(BUILDIN))	\

OBJS_DIR		= ./objs
OBJS			= $(patsubst $(SRCS_DIR)%,$(OBJS_DIR)%,$(SRCS:.c=.o))

INCLUDES		= -I $(LIBFT_DIR) -I $(PRINTFFD_DIR) -I $(HEAD_DIR)

CC				= gcc

FLAGS			= -Wall -Werror -Wextra $(INCLUDES)
# -Wall -Werror -Wextra
RLFLAGS			= -lreadline -lcurses -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

RLFLAGS2		= -lreadline -lcurses -L $(HOME)/.brew/opt/readline/lib -I $(HOME)/.brew/opt/readline/include
# Colors
GREEN 			= \033[00;32m
GREEN_B 		= \033[01;32m
YELLOW 			= \033[00;33m
RESET 			= \033[00m

# Rules
all:			$(NAME)

$(NAME):	libraries $(LIB_A) $(OBJS)
		@gcc $(FLAGS) $(OBJS) $(MAIN) $(LIB_A) -o $(NAME) $(RLFLAGS2)
		@echo "$(GREEN_B)$(NAME) successfully compiled $(RESET)"

sanitize:	 libraries $(OBJS) $(LIB_A)
		@gcc -g -fsanitize=address $(FLAGS) $(OBJS) $(MAIN) $(LIB_A) -o $(NAME)
		@echo "$(GREEN)$(NAME) successfully compiled $(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@mkdir -p $(@D)
		@gcc -c $(FLAGS) $< -o $@

$(OBJS): 			| $(OBJS_DIR)
$(OBJS_DIR):
		@mkdir $(OBJS_DIR)

libraries:			
		@printf "Making libft..." && make -C $(LIBFT_DIR) && echo "$(YELLOW)libft successfully compiled $(RESET)"
		@printf "Making printf_fd..." && make -C $(PRINTFFD_DIR) && echo "$(YELLOW)printf_fd successfully compiled $(RESET)"


clean:				
		@rm -f $(OBJS)
		@echo "$(GREEN)Successfully cleaned objects - $(NAME)$(RESET)"

fclean: 			clean
		make fclean -C $(LIBFT_DIR)
		make fclean -C $(PRINTFFD_DIR)
		@rm -f $(OBJS)
		@rm -f $(NAME)
		@rm -rf $(OBJS_DIR)
		@echo "$(GREEN)Successfully forced cleaned - $(NAME)$(RESET)"

re: 				fclean all

norme:				
		norminette ./include ./srcs ./lib/libft | awk '! /OK!/'

PHONY: 				all clean fclean re libraries norme