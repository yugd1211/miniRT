# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 19:16:12 by iyun              #+#    #+#              #
#    Updated: 2022/10/07 12:45:22 by gyyu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC_DIR			=	incs

SRCS			=	mandatory/main.c mandatory/tangent_plane.c \
					mandatory/utils/check_necessity.c mandatory/utils/color_utils.c \
					mandatory/utils/ft_atof.c mandatory/utils/ft_atoi.c \
					mandatory/utils/ft_error.c mandatory/utils/ft_split.c \
					mandatory/utils/product.c mandatory/utils/utils1.c \
					mandatory/utils/utils2.c mandatory/utils/vec_utils.c \
					mandatory/utils/ft_strncmp.c mandatory/utils/equal.c \
					mandatory/utils/ft_free.c \
					mandatory/setting/ft_color.c mandatory/setting/new_malloc.c \
					mandatory/setting/parse.c mandatory/setting/window.c \
					mandatory/setting/setting.c mandatory/setting/setting_cam_light.c \
					mandatory/setting/setting_object.c mandatory/setting/error_check.c\
					mandatory/setting/ft_light_check.c\
					mandatory/reflexion/ambient.c mandatory/reflexion/disfusion.c \
					mandatory/reflexion/light_view_correlation.c \
					mandatory/reflexion/phong_reflextion.c \
					mandatory/reflexion/specular.c \
					mandatory/illustrate/event_exit.c mandatory/illustrate/visual.c \
					mandatory/get_hit_point/hit.c mandatory/get_hit_point/hit_cylinder.c \
					mandatory/get_hit_point/hit_cone.c mandatory/get_hit_point/ft_alpha.c \
					get_next_line/get_next_line_utils.c \
					get_next_line/get_next_line.c \
					mandatory/uv_change.c mandatory/checker_or_texture.c 
OBJS			= $(SRCS:.c=.o)

BONUS_SRCS		=	bonus/main_bonus.c bonus/tangent_plane_bonus.c \
					bonus/utils/check_necessity_bonus.c bonus/utils/color_utils_bonus.c \
					bonus/utils/ft_atof_bonus.c bonus/utils/ft_atoi_bonus.c \
					bonus/utils/ft_error_bonus.c bonus/utils/ft_split_bonus.c \
					bonus/utils/product_bonus.c bonus/utils/utils1_bonus.c \
					bonus/utils/utils2_bonus.c bonus/utils/vec_utils_bonus.c \
					bonus/utils/ft_strncmp_bonus.c bonus/utils/equal_bonus.c \
					bonus/utils/ft_free_bonus.c \
					bonus/setting/ft_color_bonus.c bonus/setting/new_malloc_bonus.c \
					bonus/setting/parse_bonus.c bonus/setting/window_bonus.c \
					bonus/setting/setting_bonus.c bonus/setting/setting_cam_light_bonus.c \
					bonus/setting/setting_object_bonus.c bonus/setting/error_check_bonus.c\
					bonus/setting/ft_light_check_bonus.c\
					bonus/reflexion/ambient_bonus.c bonus/reflexion/disfusion_bonus.c \
					bonus/reflexion/light_view_correlation_bonus.c \
					bonus/reflexion/phong_reflextion_bonus.c \
					bonus/reflexion/specular_bonus.c \
					bonus/illustrate/event_exit_bonus.c bonus/illustrate/visual_bonus.c \
					bonus/get_hit_point/hit_bonus.c bonus/get_hit_point/hit_cylinder_bonus.c \
					bonus/get_hit_point/hit_cone_bonus.c bonus/get_hit_point/ft_alpha_bonus.c \
					get_next_line/get_next_line_utils_bonus.c \
					get_next_line/get_next_line_bonus.c \
					bonus/uv_change_bonus.c bonus/checker_or_texture_bonus.c 
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= minirt

all:			$(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $^ -o $@

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
