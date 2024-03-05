#------------------------- Makefile for MiniRT ----------------------------# 
################################ Colors ####################################  

BLUE 	= \033[0;34m
MAGENT 	= \033[0;35m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE_B 	= \033[1;34m
MAG_B	= \033[1;35m
WHITE 	= \033[1;37m
RESET	= \033[0m

################################# Project ###################################

NAME 	= miniRT
HEADER 	= ./include
LIBFT	= ./libft	
MLX 	= ./MLX42/include/MLX42
BIN_MLX = ./MLX42/build/libmlx42.a

################################# Sources ###################################

INIT		= init/init.c
UTILS		= utils/to_finish.c
PARSER 		= parser/aux_functions.c 	\
			parser/aux_functions2.c		\
			parser/validation.c 		\
			parser/ambient.c 			\
			parser/camera.c 			\
			parser/light.c				\
			parser/cylinder.c			\
			parser/plane.c				\
			parser/sphere.c				\
	
# MMLX		= mlx/init_render.c
OPERATIONS	= operations/vector.c 

MAND_SRCS 	= main.c $(INIT) $(PARSER) $(UTILS) $(OPERATIONS)

SRC = $(addprefix ./src/, $(MAND_SRCS))

################################# Objects ###################################

OBJS = $(MAND_SRCS:.c=.o)
OBJS_DIR = ./objs

################################# Flags #####################################

CC = gcc
CCPFLAGS = ./include/
CFLAGS = -Wall -Wextra -Werror -g -I$(HEADER) -I$(MLX)
LIBFT_MAKE = $(MAKE) -C $(LIBFT) -s
LIBFT_LIB = $(LIBFT)/libft.a

LDFLAGS = -L./MLX42/build -lm -ldl -pthread -lglfw

################################ Progress ###################################

TOTAL_FILES =	$(words $(SRC))
CURRENT_FILES = 0

define print_progress
	$(eval CURRENT_FILES=$(shell echo $$(($(CURRENT_FILES)+1))))
	@echo -n "\r$(MAG_B)Progress: $(MAGENT)$(CURRENT_FILES) / $(TOTAL_FILES) [$$((($(CURRENT_FILES) * 100) / $(TOTAL_FILES)))%] $(RESET) : $(BLUE)$(1)$(RESET) "
endef

################################# Test Sources ##############################

# TEST_SRCS	= tests/tests_amblight.c \
# TEST_OBJS	= $(TEST_SRCS:.c=.0)
# TEST_EXEC	= test_miniRT

################################# Test Rules ################################

# test: $(TEST_EXEC)
#
# $(TEST_EXEC): $(LIBFT_LIB) $(TEST_OBJS)
# 	@$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS:%=$(OBJS_DIR)/%) -o $(TEST_EXEC) $(LDFLAGS) -L$(LIBFT) -lft
# 	@echo "$(GREEN)Running tests... $(RESET)"
# 	# @./$(TEST_EXEC)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call print_progress, $(BLUE_B)Compiling:$(RESET) $<)

# clean_test:
# 	@rm -f $(TEST_OBJS)
# 	@rm -f $(TEST_EXEC)
# 	@echo "$(RED)Test objects and executable deleted$(RESET)"
#
################################# Rules ####################################

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS:%=$(OBJS_DIR)/%)
	@$(CC) $(CFLAGS) $(OBJS:%=$(OBJS_DIR)/%) -o $(NAME) $(LDFLAGS) -L$(LIBFT) -lft
	@echo ""
	@echo "$(GREEN)$(NAME) created$(RESET)"

$(LIBFT_LIB):
	@echo "$(YELLOW)Creating libft...$(RESET)"
	@$(LIBFT_MAKE)

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call print_progress, $(BLUE_B)Compiling:$(RESET) $<)

clean:
	@$(LIBFT_MAKE) clean
	@rm -rf $(OBJS_DIR) 
	@echo "$(RED)$(NAME) objects deleted$(RESET)"

fclean: clean
	@$(LIBFT_MAKE) fclean
	@rm -f $(NAME) $(TEST_EXEC)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean test clean_test re
