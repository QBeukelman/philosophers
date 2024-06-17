# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: quentin <quentin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 10:59:48 by qbeukelm          #+#    #+#              #
#    Updated: 2024/06/17 11:03:47 by quentin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Names =====
NAME = philo.a
NAME_EXECUTABLE = philo

# ===== Compile =====
CC = gcc #-fsanitize=thread
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
				init.c \

SOURCES_TOOLS = ft_atol.c \

SOURCES_UTILS = print_utils.c \
				time_utils.c \
				clean_exit.c \

SOURCES_SIM = ft_simulation_thread.c \
				ft_simulator.c \
				ft_eating.c \
				ft_check_done_conditions.c \
				ft_check_die_conditions.c \

# ===== Manage Directories =====
INC = inc
DIR_OBJ = obj

DIR_SOURCES = sources
DIR_SOURCES_INIT = sources/init
DIR_SOURCES_TOOLS = sources/tools
DIR_SOURCES_UTILS = sources/utils
DIR_SOURCES_SIM = sources/simulation

# ===== Object Files =====
OBJ = $(addprefix $(DIR_OBJ)/, $(SOURCES:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_INIT:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_TOOLS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_UTILS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_SIM:.c=.o))

# ===== Rules =====
all: $(NAME_EXECUTABLE)

$(NAME_EXECUTABLE): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Successfully compiled $(NAME_EXECUTABLE)$(RESET)"

$(DIR_OBJ)/%.o: $(DIR_SOURCES)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_INIT)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_TOOLS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_UTILS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_SIM)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $@

clean:
	@echo "$(BLUE)\nCleaning ...$(RESET)"
	@$(RM) -rf $(DIR_OBJ)
	@$(RM) -rf $(EXTRA_O)
	@$(RM) -rf $(OBJS)
	@$(RM) $(DIR_OBJ)/$(NAME)
	@echo "$(GREEN)$(BOLD)\nAll clean!\n$(RESET)"

fclean: clean
	@$(RM) $(NAME_EXECUTABLE)

re: fclean all

.PHONY: clean fclean re all