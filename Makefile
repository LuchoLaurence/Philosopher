SRCS = main.c parsing.c utils.c init.c utils2.c thread.c doing.c

SRCSB = thread.c

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g -I. -pthread

OBJ = ./objs

OBJS = $(addprefix $(OBJ)/, ${SRCS:.c=.o})

NAME = philo

all : ${NAME}

${NAME} : $(OBJS)
	$(CC) ${CFLAGS} $(OBJS) -o ${NAME}

$(OBJ)/%.o: ./%.c
	@mkdir -p $(dir $@) # Crée le répertoire "objs" s'il n'existe pas
	$(CC) $(CFLAGS) -c -o $@ $<


clean : 
	rm -rf ${OBJ}
	rm -f ${OBJS}

fclean : clean
	rm -rf ${NAME}
	
re : fclean all

.PHONY : all clean fclean re .c