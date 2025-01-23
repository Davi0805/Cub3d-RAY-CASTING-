#include "cub3d.h"

void	PutPixelToImg(t_mlx_data mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = mlx.img_addr + (y * mlx.size_line + x * (mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}