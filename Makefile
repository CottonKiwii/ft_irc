# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 15:40:11 by jwolfram          #+#    #+#              #
#    Updated: 2026/06/02 13:54:42 by jwolfram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98 -MMD -MP

RM = rm -fr

INCLUDE = -I./include

SRCS_DIR = src
OBJS_DIR = obj

SRCS = main.cpp \

OBJS = ${SRCS:%.cpp=${OBJS_DIR}/%.o}
DEPS = ${SRCS:%.cpp=${OBJS_DIR}/%.d}

OBJS_DIRS = ${sort ${dir ${OBJS}}}

ARGS = port password

DEBUG = 0

# **************************************************************************** #
#                             Compilation Targets                              #
# **************************************************************************** #
all: ${NAME}

${NAME}: ${OBJS}
		${CXX} ${CXXFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.cpp | ${OBJS_DIRS}
		${CXX} ${CXXFLAGS} ${INCLUDE} -D DEBUG=${DEBUG} -c $< -o $@
		
${OBJS_DIRS}:
		mkdir -p $@

-include ${DEPS}

# **************************************************************************** #
#                                  Cleanup                                     #
# **************************************************************************** #
clean:
		${RM} ${OBJS_DIR}

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
		./${NAME} ${ARGS}

.PHONY: all clean fclean re
