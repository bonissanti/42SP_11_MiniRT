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
TEST_N 	= miniTESTER
HEADER 	= ./include
LIBFT	= ./libft	
MLX 	= ./MLX42/include/MLX42
BIN_MLX = ./MLX42/build/libmlx42.a

################################# Sources ###################################

INIT		= init/init.c \
			init/list_objects.c
UTILS		= utils/to_finish.c
PARSER 		= parser/aux_functions.c 	\
			parser/aux_functions2.c		\
			parser/validation.c 		\
			parser/ambient.c 			\
			parser/camera.c 			\
			parser/light.c				\
			parser/cylinder.c			\
			parser/plane.c				\
			parser/sphere.c				

BVH			= bvh/create_bvh.c			\
			bvh/get_object_bbox.c		\
			bvh/get_quadrant.c			\
			bvh/sort_list.c				

RENDER		= render/render.c \

INTER		= intersection/hit.c \
			  intersection/intersections.c \
			  intersection/list.c

OPERATIONS	= operations/vector.c \
			  operations/coords.c 

MATRIX		= matrix/matrix.c \
			  matrix/inverse.c \
			  matrix/transformation.c \
			  matrix/operations.c 

TEST_DIR	= ./src/tests
MAND_SRCS 	= main.c $(INIT) $(PARSER) $(UTILS) $(OPERATIONS) $(BVH) $(RENDER) $(INTER) $(MATRIX)
TEST_SRCS 	= $(shell find $(TEST_DIR) -name '*.c')
SRC = $(addprefix ./src/, $(MAND_SRCS))

SRCS_COMMON = $(filter-out main.c, $(MAND_SRCS))
OBJS_COMMON = $(SRCS_COMMON:%.c=$(OBJS_DIR)/%.o)

################################# Objects ###################################

OBJS 		= $(MAND_SRCS:.c=.o)
OBJS_DIR 	= ./objs
TEST_OBJS	= $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJS_DIR)/%.o)

################################# Flags #####################################

CC = gcc
CCPFLAGS = ./include/
CFLAGS = -Wall -Wextra -Werror -g -I$(HEADER) -I$(MLX)
LIBFT_MAKE = $(MAKE) -C $(LIBFT) -s
LIBFT_LIB = $(LIBFT)/libft.a

LDFLAGS = -L./MLX42/build -lmlx42 -lm -ldl -pthread 

################################ Progress ###################################

TOTAL_FILES =	$(words $(SRC))
CURRENT_FILES = 0

define print_progress
	$(eval CURRENT_FILES=$(shell echo $$(($(CURRENT_FILES)+1))))
	@echo -n "\r$(MAG_B)Progress: $(MAGENT)$(CURRENT_FILES) / $(TOTAL_FILES) [$$((($(CURRENT_FILES) * 100) / $(TOTAL_FILES)))%] $(RESET) : $(BLUE)$(1)$(RESET) "
endef

# %.o: %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@
# 	$(call print_progress, $(BLUE_B)Compiling:$(RESET) $<)
#
################################# Rules ####################################

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS:%=$(OBJS_DIR)/%)
	@$(CC) $(CFLAGS) $(OBJS:%=$(OBJS_DIR)/%) -o $(NAME) $(LDFLAGS) -L$(LIBFT) -lft
	@echo ""
	@echo "$(GREEN)$(NAME) created$(RESET)"

test: CFLAGS += -D TEST
test: $(LIBFT_LIB) $(OBJS_COMMON) $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(TEST_OBJS) -o $(TEST_N) $(LDFLAGS) -L$(LIBFT) -lft
	@echo "$(GREEN)$(TEST_N) created$(RESET)"


$(LIBFT_LIB):
	@echo "$(YELLOW)Creating libft...$(RESET)"
	@$(LIBFT_MAKE)

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call print_progress, $(BLUE_B)Compiling:$(RESET) $<)

$(OBJS_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(LIBFT_MAKE) clean
	@rm -rf $(OBJS_DIR) 
	@echo "$(RED)$(NAME) objects deleted$(RESET)"

clean_t:
	@rm -f $(TEST_OBJS)
	@echo "$(RED)Test objects deleted"

fclean: clean
	@$(LIBFT_MAKE) fclean
	@rm -f $(NAME) $(TEST_N)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME) deleted$(RESET)"

fclean_t: clean_test
	@rm -f $(TEST_N)
	@echo "$(RED)$(TEST_N) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean test clean_test fclean_test re
