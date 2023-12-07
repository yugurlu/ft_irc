
NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = server.cpp \
	main.cpp \
	user.cpp \
	commands.cpp \
	channel.cpp \
	./Commands/nick.cpp \
	./Commands/pass.cpp \
	./Commands/user.cpp \
	./Commands/quit.cpp \
	./Commands/ping.cpp \
	./Commands/join.cpp \
	./Commands/kick.cpp \
	./Commands/part.cpp \
	./Commands/privmsg.cpp \
	./Commands/topic.cpp \
	./Commands/mode.cpp \
	./Commands/cap.cpp \
	./Commands/notice.cpp \
	./Commands/who.cpp

OBJS = ${SRCS:.cpp=.o}

.cpp.o:
	@${CC} ${FLAGS} -c $< -o ${<:.cpp=.o}

RM = rm -f

${NAME}: ${OBJS}
	@${CC} ${FLAGS} -o ${NAME} ${OBJS}

all: ${NAME}
	@echo "\033[33mCompile Completed!\033[0m"

bonus: all

clean:
	@${RM} *.o */*.o */*/*.o

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
