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
			parser/validation.c 		\
			parser/ambient.c 			\
			parser/ambient_set_valid.c 	\
			parser/camera.c 			\
			parser/camera_set.c			\
			parser/camera_validation.c	\
			parser/light.c				\
			parser/sphere.c				\

MAND_SRCS 	= main.c $(INIT) $(PARSER) $(UTILS)

SRC = $(addprefix ./src/, $(MAND_SRCS))

################################# Objects ###################################

OBJS = $(MAND_SRCS:.c=.o)
OBJS_DIR = ./objs

################################# Flags #####################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(HEADER) -I$(MLX)
LIBFT_MAKE = $(MAKE) -C $(LIBFT) -s
LIBFT_LIB = $(LIBFT)/libft.a

LDFLAGS = -L./MLX42/build -lm

################################ Progress ###################################

TOTAL_FILES = $(words $(SRC))
CURRENT_FILES = 0

define print_progress
	$(eval CURRENT_FILES=$(shell echo $$(($(CURRENT_FILES)+1))))
	@echo -n "\r$(MAG_B)Progress: $(MAGENT)$(CURRENT_FILES) / $(TOTAL_FILES) [$$((($(CURRENT_FILES) * 100) / $(TOTAL_FILES)))%] $(RESET) : $(BLUE)$(1)$(RESET) "
endef

################################# Rules #####################################

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
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
