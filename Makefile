ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc.so
HOSTLIB := libft_malloc_$(HOSTTYPE).so
FLAGS := -Wall -Wextra -Werror -fPIC
INC := -Iincludes/ -Ilibft
LIBFT_DIR := ./libft/
LIB := -lpthread -Llibft -lft
SRC_DIR := src
SRC_FILE := defragment.c
SRC_FILE += free.c 
SRC_FILE += limit.c 
SRC_FILE += locate.c 
SRC_FILE += malloc.c 
SRC_FILE += map.c 
SRC_FILE += realloc.c 
SRC_FILE += show.c 
SRC_FILE += unmap.c
SRC := $(addprefix $(SRC_DIR)/,$(SRC_FILE))
OBJ_DIR := objects
OBJ	:= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o)) 

all : mkdir lft $(NAME)

mkdir :
	@mkdir -p $(OBJ_DIR)

lft :
	@make -C $(LIBFT_DIR)

$(NAME) : $(OBJ)
	@gcc -shared -fPIC $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ))) $(INC) $(LIB) -o $(HOSTLIB)
	@ln -sf $(HOSTLIB) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@gcc -fPIC $(INC) -c $< -o $(OBJ_DIR)/$(notdir $@)

clean :
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean :
	@make fclean -C $(LIBFT_DIR)
	@rm $(NAME)
	@rm $(HOSTLIB)

re : fclean all

.PHONY : all clean fclean re
