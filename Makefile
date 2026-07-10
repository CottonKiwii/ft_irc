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
	   Command \
	   Channel \
	   handlers/handleCap \
	   handlers/handleJoin \
	   handlers/handleKick \
	   handlers/handleMode \
	   handlers/handleNick \
	   handlers/handleNotice \
	   handlers/handlePart \
	   handlers/handlePass \
	   handlers/handlePing \
	   handlers/handlePong \
	   handlers/handlePrivmsg \
	   handlers/handleQuit \
	   handlers/handleTopic \
	   handlers/handleUnknown \
	   handlers/handleUser \
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
		--leak-check=full \
		--show-leak-kinds=all \
		--track-fds=all \
		./${NAME} ${ARGS}

.PHONY: all clean fclean re run valgrind
