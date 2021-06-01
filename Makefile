SRCS			= srcs/philo_one/main.c srcs/philo_one/guetters.c srcs/philo_one/guetters2.c srcs/philo_two/main.c srcs/philo_three/main.c srcs/philo_one/philosophers.c

OBJS_ONE	= srcs/philo_one/main.o  srcs/philo_one/guetters.o srcs/philo_one/guetters2.o srcs/philo_one/philosophers.o

OBJS_TWO	= srcs/philo_two/main.o

OBJS_THREE	= srcs/philo_three/main.o

INC			=  -I inc/

CC			= gcc -pthread

RM			= rm -f

.c.o:
			$(CC) -c $< -o $(<:.c=.o) $(INC)

all:			one two three

one :			$(OBJS_ONE)
				$(CC) $(INC) $(OBJS_ONE) -o philo_one
two :			$(OBJS_TWO)
				$(CC) $(INC) $(OBJS_TWO) -o philo_two
three :			$(OBJS_THREE)
				$(CC) $(INC) $(OBJS_THREE) -o philo_three
clean:
				$(RM) $(OBJS_ONE) $(OBJS_TWO) $(OBJS_THREE)
fclean:			clean
				$(RM) philo_one philo_two philo_three
re:				fclean all

.PHONY:			all clean fclean re bonus