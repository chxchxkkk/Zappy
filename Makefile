AI_NAME	=	zappy_ai

AI_DIR	=	ai_src

GRAPHIC_DIR	=	./graphical_client

SRV_NAME	=	zappy_server

SRV_DIR	=	server_src

SRV_SRC	=	$(wildcard $(SRV_DIR)/*.c) $(wildcard $(SRV_DIR)/**/*.c)

SRV_OBJ	=	${SRV_SRC:.c=.o}

CC	=	gcc

CFLAGS	=	-W -Wall -Wextra -fms-extensions -I ${SRV_DIR}/include

LDFLAGS	=	-L ${SRV_DIR}/lib/list -llist -lm

all: zappy_server zappy_ai zappy_graphic

zappy_ai:
	echo -ne "#!/bin/bash\nexport PYTHONPATH=\$$PYTHONPATH:\$$PWD/ai_src\npython3.6 ${AI_DIR}/main.py \$$@" > ${AI_NAME}
	chmod +x ${AI_NAME}

run_ai: zappy_ai
	./zappy_ai a b c

zappy_server: ${SRV_OBJ}
	make -C $(SRV_DIR)/lib/list
	gcc -o ${SRV_NAME} ${SRV_OBJ} $(CFLAGS) $(LDFLAGS)

zappy_graphic:
	make -C $(GRAPHIC_DIR)

clean:
	make clean -C $(SRV_DIR)/lib/list
	rm -rf ${SRV_OBJ}

fclean: clean
	make fclean -C $(SRV_DIR)/lib/list
	rm -rf ${SRV_NAME}
	rm -rf ${AI_NAME}

re: fclean all

install: install_ai install_server

install_ai:	pip3 install -r requirements.txt

install_server:

.PHONY:	re fclean clean all zappy_ai zappy_server install install_ai install_server zappy_graphic
