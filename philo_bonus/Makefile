CC=CC
FLAGS= -Wall -Werror -Wextra
RM=rm -rf
NAME=philo_bonus

FILES = philo_bonus philo_init_bonus philo_utlis_bonus philo_add_bonus

OBJ=$(FILES:=.o)

all: $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(FLAGS) -c $<

$(NAME): $(OBJ) philo_bonus.h
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) 
clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME) 

re: fclean all