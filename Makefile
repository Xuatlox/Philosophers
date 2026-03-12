.PHONY : all clean fclean re
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = philo.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_calloc.c \
		philo_utils.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ) : $(OBJ_DIR) $(SRC)
	cd $(OBJ_DIR) && $(CC) $(CFLAGS) -c $(addprefix ../, $(SRC))

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)
