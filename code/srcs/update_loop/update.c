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
		PlayerRotateRight(&head->player);
	if(moves->l_key == true) 
		PlayerRotateLeft(&head->player);
}

// Game loop that will read player movements, cast rays and draw the map accordingly to its location
int UpdateLoop(t_cub *head)
{
	UpdatePlayerPosition(head);
	Raycaster(head);

	// put to the screen
    mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
	return (0);
}