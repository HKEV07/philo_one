CC=CC
FLAGS= -Wall -Werror -Wextra
RM=rm -rf
NAME=philo
FILES = philo philo_utlis philo_init philo_add

OBJ=$(FILES:=.o)

all: $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $<

$(NAME): $(OBJ) philo.h
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) 
clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME) 

re: fclean all