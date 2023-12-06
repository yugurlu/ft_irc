NAME = ircserv
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g 
OBJECTS = $(FILE:.cpp=.o)
FILE = server.cpp \
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
RM = rm -rf

all: $(NAME)

$(NAME): $(FILE)
	$(CC) $(CPPFLAGS) -o $(NAME) $(FILE)
.c.o:
	${CC} ${CPPFLAGS} -C $< -o ${OBJECTS}
clean:
	$(RM) -f *.o
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re