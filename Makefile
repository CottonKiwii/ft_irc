NAME = ircserv

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98 -MMD -MP

RM = rm -fr

INCLUDE = -I./include

SRCS_DIR = src
OBJS_DIR = obj

SRCS = classes/Server/Server \
	   classes/Server/utils \
	   classes/Client/Client \
	   classes/Client/utils \
	   classes/Channel/Channel \
	   classes/Channel/utils \
	   Command \
	   handlers/command/join \
	   handlers/command/kick \
	   handlers/command/mode \
	   handlers/command/nick \
	   handlers/command/notice \
	   handlers/command/part \
	   handlers/command/pass \
	   handlers/command/ping \
	   handlers/command/pong \
	   handlers/command/privmsg \
	   handlers/command/quit \
	   handlers/command/topic \
	   handlers/command/user \
	   handlers/command/unknown \
	   handlers/command/unhandled \
	   privmsgHandlers/handleClientToClient \
	   privmsgHandlers/handleClientToChannel \
	   modeHandlers/modeUserUnknown \
	   modeHandlers/modeUseri \
	   modeHandlers/modeChanUnknown \
	   modeHandlers/modeChani \
	   modeHandlers/modeChant \
	   modeHandlers/modeChank \
	   modeHandlers/modeChano \
	   modeHandlers/modeChanl \


OBJS = ${SRCS:%=${OBJS_DIR}/%.o}
DEPS = ${SRCS:%=${OBJS_DIR}/%.d}

OBJS_DIRS = ${sort ${dir ${OBJS}}}

ARGS = 6667 hello

DEFINES = -D DEBUG=0

# **************************************************************************** #
#                             Compilation Targets                              #
# **************************************************************************** #
all: ${NAME}

${NAME}: ${OBJS} obj/main.o
		${CXX} ${CXXFLAGS} ${INCLUDE} $^ -o ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.cpp | ${OBJS_DIRS}
		bear --append -- ${CXX} ${CXXFLAGS} ${INCLUDE} ${DEFINES} -c $< -o $@
		
${OBJS_DIRS}:
		mkdir -p $@

-include ${DEPS}

# **************************************************************************** #
#                                  Cleanup                                     #
# **************************************************************************** #
clean:
		${RM} ${OBJS_DIR}
		${RM} .cache
		${RM} compile_commands.json

fclean: clean
		${RM} ${NAME}

re: fclean all

# **************************************************************************** #
#                                  Other                                       #
# **************************************************************************** #
run:	${NAME}
		./${NAME} ${ARGS}

valgrind: ${NAME}
		valgrind \
		--track-fds=all \
		./${NAME} ${ARGS}

client: PROFILE=gridis
client:
	irssi --config=profiles/${PROFILE} -c localhost

.PHONY: all clean fclean re run valgrind
