

DIRINC = ./includes/

DIRSRC = ./srcs/

SRC =   main \
		utils \

SRCS = $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

CFLAGS = -Wall -Wextra -Werror -I $(DIRINC)
CC = cc
LIBC = ar rc
RM = rm -f

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o philo

clean:
	make clean -C $(DIRLIB)

fclean: clean
	make fclean -C $(DIRLIB)
	rm -f philo

re: fclean all

