# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 10:25:13 by rklein            #+#    #+#              #
#    Updated: 2021/11/11 11:22:05 by rklein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc.so
HOSTLIB := libft_malloc_$(HOSTTYPE).so
FLAGS := -Wall -Wextra -Werror -fPIC
INC := -Iincludes/
LIB := -lpthread
UTIL_DIR := utils
UTIL_FILE := ft_memcpy.c 
UTIL_FILE += ft_memmove.c 
UTIL_FILE += ft_memset.c 
UTIL_FILE += ft_putchar.c 
UTIL_FILE += ft_puthex.c 
UTIL_FILE += ft_putsize.c 
UTIL_FILE += ft_putstr.c
UTIL := $(addprefix $(UTIL_DIR)/,$(UTIL_FILE)) 
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
SRC_FILE += $(UTIL)
SRC := $(addprefix $(SRC_DIR)/,$(SRC_FILE))
OBJ_DIR := objects
OBJ	:= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o)) 

all : mkdir $(NAME)

mkdir :
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
	@gcc -shared -fPIC $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ))) $(INC) $(LIB) -o $(HOSTLIB)
	@ln -sf $(HOSTLIB) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@gcc -fPIC $(INC) -c $< -o $(OBJ_DIR)/$(notdir $@)

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)
	@rm -f libft_malloc_*.so
	
re : fclean all

.PHONY : all clean fclean re
