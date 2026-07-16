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
	   handlers/command/pass \
	   handlers/command/nick \
	   handlers/command/user \
	   handlers/command/ping \
	   handlers/command/pong \
	   handlers/command/quit \
	   handlers/command/join \
	   handlers/command/invite \
	   handlers/command/part \
	   handlers/command/kick \
	   handlers/command/topic \
	   handlers/command/mode \
	   handlers/command/privmsg \
	   handlers/command/notice \
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

client: PROFILE=${USER}
client:
	irssi --config=profiles/${PROFILE} -c localhost

.PHONY: all clean fclean re run valgrind
