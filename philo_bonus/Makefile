NAME = philo

DIRINC = ./includes/

DIRSRC = ./srcs/

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC =   main \
		utils \
		utils2 \
		init \
		actions \
		simulation \
		monitor \


SRCS = $(addprefix ${DIRSRC}, $(addsuffix _bonus.c, ${SRC}))

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o philo

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

re: fclean all

