NAME = philo.a

CC = cc

CFLAGS = -I $(DIRINC) -Wall -Wextra -Werror

LIBC = ar rc
RM = rm -f

DIRINC = ./includes/philo.h

DIRSRC = ./srcs/

SRC =   main \
		utils \
		init \

SRCS = $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o philo $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

re: fclean all

