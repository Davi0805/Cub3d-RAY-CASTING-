#include "cub3d.h"

static void UpdatePlayerPosition(t_cub *head)
{
	t_moves *moves = &head->player.moves;
	if(moves->w_key == true) 
		PlayerForward(&head->player, head->map, head);
	if(moves->s_key == true) 
		PlayerBackword(&head->player, head->map, head);
	if(moves->a_key == true) 
		PlayerLeft(&head->player, head->map, head);
	if(moves->d_key == true) 
		PlayerRight(&head->player, head->map, head);
	if(moves->r_key == true) 
		PlayerRotateRight(&head->player);
	if(moves->l_key == true) 
		PlayerRotateLeft(&head->player);
}

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

int KeyPressed(int key, t_cub *head)
{
	if (key == XK_Right)
		head->player.moves.r_key = true;
	else if (key == XK_Left)
		head->player.moves.l_key = true;
	else if (key == XK_w)
		head->player.moves.w_key = true;
	else if (key == XK_s)
		head->player.moves.s_key = true;
	else if (key == XK_a)
		head->player.moves.a_key = true;
	else if (key == XK_d)
		head->player.moves.d_key = true;
	else if (key == XK_Escape)
		ExitFun(head);
	return (0);
}

int KeyReleased(int key, t_cub *head)
{
	if (key == XK_Right)
		head->player.moves.r_key = false;
	if (key == XK_Left)
		head->player.moves.l_key = false;
	if (key == XK_w)
		head->player.moves.w_key = false;
	if (key == XK_s)
		head->player.moves.s_key = false;
	if (key == XK_a)
		head->player.moves.a_key = false;
	if (key == XK_d)
		head->player.moves.d_key = false;
	return (0);
}
