#include "cub3d.h"

// This checks for keys that are pressed (flaged as true) and changes
// player dir and pos values
static void UpdatePlayerPosition(t_cub *head)
{
	t_moves *moves = &head->player.moves;
	if(moves->w_key == true) 
		PlayerForward(&head->player, head->map, head);
	if(moves->s_key == true) 
		PlayerBackward(&head->player, head->map, head);
	if(moves->a_key == true) 
		PlayerLeft(&head->player, head->map, head);
	if(moves->d_key == true) 
		PlayerRight(&head->player, head->map, head);
	if(moves->r_key == true) 
		PlayerRotateRight(head, &head->player);
	if(moves->l_key == true) 
		PlayerRotateLeft(head, &head->player);
}

// Game loop that will read player movements, cast rays and draw the map accordingly to its location
int UpdateLoop(t_cub *head)
{
	// deltaTime is used to turn the speed of the game independent of processing time and FPS meter
	head->deltaTime = DeltaTime(&head->time);
    gettimeofday(&head->time, NULL); // update the time for the next frame

	UpdatePlayerPosition(head);
	Raycaster(head);

	// put to the screen
    mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
	

	// FPS meter on screen
	double fps = 1 / head->deltaTime;
	char *fps_str = ft_itoa((int)fps);
	mlx_string_put(head->mlx.mlx_ptr, head->mlx.win_ptr, WIDTH - 50, 15, 0xFFFFFF, "FPS: ");
	mlx_string_put(head->mlx.mlx_ptr, head->mlx.win_ptr, WIDTH - 25, 15, 0xFFFFFF, fps_str);
	free(fps_str);
	return (0);
}