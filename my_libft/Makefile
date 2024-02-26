#-------------------------- Makefile libft 2.0 ----------------------------#  
################################ Colors #################################### 

GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[1;37m

############################### PROJECT FILES ###############################

SRC = ../src/ft_atoi.c ../src/ft_bzero.c ../src/ft_calloc.c ../src/ft_isalnum.c \
	../src/ft_isalpha.c ../src/ft_isascii.c ../src/ft_isdigit.c ../src/ft_isprint.c \
	../src/ft_itoa.c ../src/ft_lstadd_back.c ../src/ft_lstadd_front.c ../src/ft_lstclear.c \
	../src/ft_lstdelone.c ../src/ft_lstiter.c ../src/ft_lstlast.c ../src/ft_lstmap.c ../src/ft_lstnew.c \
	../src/ft_lstsize.c ../src/ft_memchr.c ../src/ft_memcmp.c ../src/ft_memcpy.c ../src/ft_memmove.c \
	../src/ft_memset.c ../src/ft_putchar_fd.c ../src/ft_putendl_fd.c ../src/ft_putnbr_fd.c ../src/ft_putstr_fd.c \
	../src/ft_split.c ../src/ft_split_space.c ../src/ft_strchr.c ../src/ft_strdup.c  ../src/ft_striteri.c ../src/ft_strjoin.c \
	../src/ft_strlcat.c ../src/ft_strlcpy.c ../src/ft_strlen.c ../src/ft_strmapi.c ../src/ft_strncmp.c ../src/ft_isspace.c \
	../src/ft_strnstr.c ../src/ft_strrchr.c ../src/ft_strtrim.c ../src/ft_substr.c ../src/ft_tolower.c \
	../src/ft_toupper.c ../src/get_next_line.c ../src/get_next_line_utils.c ../src/ft_printf.c ../src/ft_printf_utils.c \
	../src/print_char.c ../src/print_hex_d.c ../src/print_int.c ../src/print_percent.c ../src/print_pointer.c ../src/print_string.c \
	../src/print_unsign_int.c

HEADER = ../include/libft.h ../include/get_next_line.h ../include/ft_printf.h
OBJ = $(addprefix ./src/, $(SRC:.c=.o))
NAME = libft.a

############################### COMPILATION #################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

################################## RULES ####################################

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

############################### NORM RULES ##################################

norm:
	@echo "$(YELLOW)Norminette...$(WHITE)"
	@norminette $(SRC) $(HEADER)
	@echo "$(GREEN)Norminette done$(WHITE)"

############################### CLEAN RULES #################################

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

