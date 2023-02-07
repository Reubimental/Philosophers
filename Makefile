NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR := src
OBJDIR := objects
INC := include/
SRC := $(SRCDIR)/utils.c	$(SRCDIR)/initialize.c	$(SRCDIR)/philo_behaviour.c
OBJ := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRCDIR)/philosophers.c -I $(INC) $(OBJ) -o $(NAME)
	@clear
	@printf "\e[33m""\e[1m""\n					How to use:\n""\e[0m"
	@printf "\e[32m""		./philo ""\e[34m""num_of_philosopers time_to_die time_to_eat time_to_sleep [minimum_each_philosopher_must_eat]\n\n""\e[0m"
	@printf "\e[31m""\e[1m""Example\n""\e[0m"
	@printf "\e[32m""		./philo ""\e[34m""5 200 20 20 50\n\n""\e[0m"
	@printf "\e[35m""This will set it so that 5 philosophers have 200 miliseconds to die, they take 20 milliseconds to eat and sleep\n""\e[0m"
	@printf "\e[33m""and they must eat at least 50 times each.\n\n""\e[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re