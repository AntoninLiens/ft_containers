# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aliens <aliens@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 17:13:09 by aliens            #+#    #+#              #
#    Updated: 2022/09/05 17:25:56 by aliens           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = 		c++

CXXFLAGS =	-Wall -Wextra -Werror -std=c++98

FT_NAME =		ft_containers
STD_NAME =		std_containers

FT_SRCS =		ft_main.cpp
STD_SRCS =		std_main.cpp

FT_OBJS =		$(FT_SRCS:.cpp=.o)
STD_OBJS =		$(STD_SRCS:.cpp=.o)

.cpp.o:					
			$(CXX) $(CXXFLAGS) -c $^ -o $@

all : 		$(FT_NAME) $(STD_NAME)

$(FT_NAME):	$(FT_OBJS)
			$(CXX) -o $(FT_NAME) $(CXXFLAGS) $(FT_OBJS)

$(STD_NAME): $(STD_OBJS)
			 $(CXX) -o $(STD_NAME) $(CXXFLAGS) $(STD_OBJS)

clean:
			rm -f $(FT_OBJS)
			rm -f $(STD_OBJS)

fclean: 	clean
			rm -f $(FT_NAME)
			rm -f $(STD_NAME)

re: 		fclean all

.PHONY: 	re clean fclean all
