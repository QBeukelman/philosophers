# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: qbeukelm <qbeukelm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/18 10:59:48 by qbeukelm      #+#    #+#                  #
#    Updated: 2023/04/05 09:15:32 by qbeukelm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ===== Names =====
NAME = philo.a
NAME_EXCUITABLE = philo


# ===== Compile =====
CC = gcc -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror


# ===== Colors =====
BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
RESET	:= \033[0m


# ===== Sources =====
SOURCES = philo.c \

SOURCES_INIT = check_args.c \

SOURCES_TOOLS = ft_atol.c \

SOURCES_UTILS = sim_utils.c \
				time_utils.c \

SOURCES_SIM = ft_simulation_thread.c \
				ft_simulator.c \
				ft_eating.c \
				ft_eating_operations.c \
				ft_check_end_conditions.c \


# ===== Manage Directories =====
INC = inc
DIR_OBJ = obj

DIR_SOURCES = sources
DIR_SOURCES_INIT = sources/init
DIR_SOURCES_TOOLS = sources/tools
DIR_SOURCES_UTILS = sources/utils
DIR_SOURCES_SIM = sources/simulation

O_SOURCES = $(SOURCES:%.c=$(DIR_OBJ)/$(DIR_SOURCES)/%.o)
O_SOURCES_INIT = $(SOURCES_INIT:%.c=$(DIR_OBJ)/$(DIR_SOURCES_INIT)/%.o)
O_SOURCES_TOOLS = $(SOURCES_TOOLS:%.c=$(DIR_OBJ)/$(DIR_SOURCES_TOOLS)/%.o)
O_SOURCES_UTILS = $(SOURCES_UTILS:%.c=$(DIR_OBJ)/$(DIR_SOURCES_UTILS)/%.o)
O_SOURCES_SIM = $(SOURCES_SIM:%.c=$(DIR_OBJ)/$(DIR_SOURCES_SIM)/%.o)

$(DIR_OBJ)/$(DIR_SOURCES)/%.o: $(DIR_SOURCES)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(DIR_OBJ)/$(DIR_SOURCES_INIT)/%.o: $(DIR_SOURCES_INIT)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(DIR_OBJ)/$(DIR_SOURCES_TOOLS)/%.o: $(DIR_SOURCES_TOOLS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(DIR_OBJ)/$(DIR_SOURCES_UTILS)/%.o: $(DIR_SOURCES_UTILS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(DIR_OBJ)/$(DIR_SOURCES_SIM)/%.o: $(DIR_SOURCES_SIM)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	


# ===== Rules =====
all: $(DIR_OBJ)/$(NAME)

$(DIR_OBJ)/$(NAME): $(O_SOURCES) $(O_SOURCES_INIT) $(O_SOURCES_TOOLS) $(O_SOURCES_UTILS) $(O_SOURCES_SIM)
	@$(AR) rcs $@ $^
	@ranlib $@
	@echo "$(BLUE)$(BOLD)\nCompiling program: philosophers ...$(RESET)"
	@$(CC) -o $(NAME_EXCUITABLE) $(DIR_SOURCES)/$(SOURCES) $(DIR_SOURCES_INIT)/*.c $(DIR_SOURCES_TOOLS)/*.c $(DIR_SOURCES_UTILS)/*.c $(DIR_SOURCES_SIM)/*.c $(DIR_OBJ)/$(NAME)
	@echo "$(GREEN)$(BOLD)\nCompile sucessfull!\n$(RESET)"

clean:
	@echo "$(BLUE)\nCleaning ...$(RESET)"
	@$(RM) -rf $(DIR_OBJ)
	@$(RM) -rf $(EXTRA_O)
	@$(RM) -rf $(OBJS)
	@$(RM) $(DIR_OBJ)/$(NAME)
	@echo "$(GREEN)$(BOLD)\nAll clean!\n$(RESET)"

fclean: clean
	@$(RM) $(NAME_EXCUITABLE)

re: fclean all

.PHONY: clean fclean re all
