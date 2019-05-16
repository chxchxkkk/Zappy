AI_NAME	=	zappy_ai

AI_DIR	=	ai_src

SRV_NAME	=	zappy_server

SRV_SRC	=	$(wildcard server_src/*.c)

SRV_OBJ	=	${SRV_SRC:.c=.o}

CFLAGS	=	-Wall -Wextra

zappy_ai:
	echo -ne "#!/bin/bash\npython3 ${AI_DIR}/main.py" > ${AI_NAME}
	chmod +x ${AI_NAME}

zappy_server: ${SRV_OBJ}
	gcc -o ${SRV_NAME} ${SRV_OBJ}

all: zappy_server zappy_ai

clean:
	rm -rf ${SRV_OBJ}

fclean: clean
	rm -rf ${SRV_NAME}
	rm -rf ${AI_NAME}

re: fclean all

install: install_ai install_server

install_ai:	pip3 install -r requirements.txt

install_server:

.PHONY:	re fclean clean all zappy_ai zappy_server install install_ai install_server