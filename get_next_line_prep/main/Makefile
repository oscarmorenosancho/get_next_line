# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 15:40:18 by omoreno-          #+#    #+#              #
#    Updated: 2022/10/05 16:02:40 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = get_next_line.c\
	get_next_line_utils.c

SRCB = get_next_line_bonus.c\
	get_next_line_utils_bonus.c

OBJ := $(SRC:.c=.o)
OBJB := $(SRCB:.c=.o)
DEPS = $(SRC:.c=.d)
DEPSB = $(SRCB:.c=.d)
CC	= 	gcc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
RM	= 	rm -f
LIBC	= 	ar -rcs
HEADER = get_next_line.h
CFLAG_BUFSIZE = -D BUFFER_SIZE=50

%.o : %.c ${HEADER}
	${CC} ${CFLAGS} ${CFLAG_BUFSIZE} -I ${HEADER} -c $< -o ${<:.c=.o}

all : $(NAME) 

-include: $(DEPS)
$(NAME) : $(OBJ) $(HEADER)
	$(LIBC) $(NAME) $(OBJ)

-include: $(DEPS) $(DEPSB)
bonus: $(OBJ) $(OBJB)  $(HEADER)
	$(LIBC) $(NAME) $(OBJ) $(OBJB)
	@touch $@

clean :
	$(RM) $(OBJ)
	$(RM) $(OBJB)
	$(RM) $(DEPS)
	$(RM) $(DEPSB)

fclean : clean
	$(RM) $(NAME)
	$(RM) bonus

re: fclean all

.PHONY : clean fclean re all