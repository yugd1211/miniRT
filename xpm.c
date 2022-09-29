#include "libmlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# define X_BUTTON 17
# define KEY_ESC 53
# define KEY_RELEASE 3

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		map;
	t_img		normal_map;
	int			width;
	int			height;
}	t_mlx;

int	ft_close(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int	main()
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 2040, 1020, "earth");
	// mlx.win = mlx_new_window(mlx.mlx, 3040, 1020, "earth");
	mlx.map.ptr = mlx_xpm_file_to_image(mlx.mlx, "img_src/earth_map.xpm",
			&mlx.map.width, &mlx.map.height);
	// mlx.normal_map.ptr = mlx_xpm_file_to_image(mlx.mlx, "img_src/earth_normal_map.xpm",
	// 		&mlx.map.width, &mlx.map.height);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.map.ptr, 0, 0);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.normal_map.ptr, 0, 0);

	mlx_hook(mlx.win, X_BUTTON, 0, &ft_close, &mlx);
	mlx_hook(mlx.win, KEY_RELEASE, 0, &key_release, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
