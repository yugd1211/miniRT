# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 19:16:12 by iyun              #+#    #+#              #
#    Updated: 2022/09/29 19:27:47 by iyun             ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

SRCS			=	mandatory/main.c mandatory/tangent_plane.c \
					mandatory/utils/check_necessity.c mandatory/utils/color_utils.c \
					mandatory/utils/ft_atof.c mandatory/utils/ft_atoi.c \
					mandatory/utils/ft_error.c mandatory/utils/ft_spilt.c \
					mandatory/utils/product.c mandatory/utils/utils1.c \
					mandatory/utils/utils2.c mandatory/utils/vec_utils.c \
					mandatory/setting/ft_color.c mandatory/setting/new_malloc.c \
					mandatory/setting/parse.c mandatory/setting/window.c \
					mandatory/reflexion/ambient.c mandatory/reflexion/disfusion.c \
					mandatory/reflexion/light_view_correlation.c \
					mandatory/reflexion/phong_reflexion.c \
					mandatory/reflexion/specular.c \
					mandatory/illustrate/event_exit.c mandatory/illustrate/visual.c \
					mandatory/get_hit_point/hit.c mandatory/get_hit_point/hit_cylinder.c \
					mandatory/get_hit_point/hit_cone.c
OBJS			= $(SRCS:.c=.o)

BONUS_SRCS		=	bonus/ft_atoi_bonus.c bonus/ft_split_bonus.c bonus/ft_split_size_bonus.c \
					bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c \
					bonus/bresenham_line_bonus.c bonus/ft_axis_vector_bonus.c bonus/key_hook_bonus.c \
					bonus/matrix_bonus.c bonus/ret_mag_bonus.c bonus/draw_bonus.c bonus/fdf_utils_bonus.c \
					bonus/ft_ret_bonus.c bonus/key_hook_move_bonus.c bonus/mouse_hook_bonus.c \
					bonus/fdf_bonus.c bonus/main_bonus.c bonus/mouse_wheel_hook_bonus.c
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= fdf

all:			$(NAME)

ifdef 			WITH_BONUS
    			OBJECTS = $(BONUS_OBJS)
else
    			OBJECTS = $(OBJS)
endif

$(NAME):		$(OBJECTS)
				$(CC) -I /usr/local/include/ -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJECTS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

bonus:			
				@make WITH_BONUS=1 all

.PHONY:			all clean fclean re bonus