# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/23 17:38:02 by iwillens          #+#    #+#              #
#    Updated: 2022/12/23 16:22:21 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computor

CC = clang++
CCFLAGS = -Wall -Werror -Wextra -std=c++98

SRC_DIR = ./srcs
OBJ_DIR = ./build
INC_DIR = ./includes

INCLUDES = ${INC_DIR}/Equation.hpp \
			${INC_DIR}/Term.hpp \
			${INC_DIR}/Double.hpp

SRCS = main.cpp \
	${SRC_DIR}/Equation.cpp \
	${SRC_DIR}/Term.cpp \
	${SRC_DIR}/Double.cpp



OBJS = $(patsubst ${SRC_DIR}/%.cpp, ${OBJ_DIR}/%.o, ${SRCS})
DEPENDS = $(patsubst %.o, %.d, ${OBJS})

all: ${NAME}

${NAME}: ${OBJS} ${INCLUDES}
	@${CC} ${CCFLAGS} ${OBJS} -I. -I ${INC_DIR} -o ${NAME}
	@echo "\033[92m.${NAME} is built. \033[0m"

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp ${INC_DIR} ${INCLUDES}
	@mkdir -p $(dir $@)
	@echo -n "."
	@${CC} ${CCFLAGS} -MMD -c  $< -I. -I ${INC_DIR} -o $@

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -rf ./${NAME}

re: fclean all

-include $(FT_DEPENDS)
