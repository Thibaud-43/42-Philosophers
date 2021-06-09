SRCS			= srcs/main.c srcs/guetters.c srcs/guetters2.c srcs/philosophers.c srcs/routine.c srcs/utils.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc -pthread
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I inc/
LIBS			=  -lpthread

NAME			= philo_one

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re