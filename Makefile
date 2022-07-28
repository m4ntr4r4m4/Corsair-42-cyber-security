
SRC		=	./corsair.c

OBJ		=	${SRC:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/ -I /sgoinfre/students/ahammoud/homebrew/opt/openssl@1.1/include/ 

LIBFT.a	=	make -C  ./libft bonus 

CC		=	gcc

NAME	=	corsair
CFLAGS	=	-Wall -Wextra -Ofast -g /sgoinfre/students/ahammoud/homebrew/opt/openssl@1.1/lib/*.a 
${NAME}	:	${OBJ}
			@${LIBFT.a}
			${CC} ${CFLAGS} ${OBJ} ./libft/libft.a -o ${NAME}


all		:	${NAME}

RM		=	rm -f

clean	:
			${RM} ${OBJ}
			make -C ./libft/ clean

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re

