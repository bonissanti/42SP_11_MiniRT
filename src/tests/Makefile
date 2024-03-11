#-------------------------- Makefile for tests ----------------------------#

################################ Colors ####################################  

BLUE    = \033[0;34m
MAGENT  = \033[0;35m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE_B  = \033[1;34m
MAG_B   = \033[1;35m
WHITE   = \033[1;37m
RESET   = \033[0m

################################# Project ###################################

include ../../Makefile
TEST_EXEC    = miniRT_test

################################# Sources ###################################

TEST_AMBLIGHT	= tests_amblight.c

MAND_SRCS		= $(TEST_AMBLIGHT)

SRC = $(addprefix ./src/, $(MAND_SRCS))

################################# Objects ###################################

OBJS = $(MAND_SRCS:.c=.o)
OBJS_DIR = ./objs

################################# Flags #####################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I.

################################ Test Rules ################################

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE_B)Compiling:$(RESET) $<"

test: $(OBJS:%=$(OBJS_DIR)/%)
	@$(CC) $(CFLAGS) $(OBJS:%=$(OBJS_DIR)/%) -o $(NAME) $(LDFLAGS)
	@echo "$(BLUE_B)Running tests...$(RESET)"

# clean:
	# @rm -rf $(OBJS_DIR) 
	# @echo "$(RED)$(TEST_EXEC) objects deleted$(RESET)

fclean_test:
	@rm -f $(TEST_EXEC)
	@echo "$(RED)$(TEST_EXEC) deleted$(RESET)"

re: fclean_test test
