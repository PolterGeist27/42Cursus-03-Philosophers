NAME = philo

DIRINC = ./includes/

DIRSRC = ./srcs/

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC =   main \
		utils \
		init \
		actions \
		simulation \

SRCS = $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o philo

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

re: fclean all

