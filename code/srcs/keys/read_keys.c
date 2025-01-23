#include "cub3d.h"



int ReadKeys(int key, t_cub *head)
{
    if (key == XK_Escape)
        ExitFun(head);
    else if(key == XK_w) 
        PlayerForward(&head->player, head->map);
    else if(key == XK_s) 
        PlayerBackword(&head->player, head->map);
    else if(key == XK_a)
        PlayerLeft(&head->player, head->map);
    else if(key == XK_d)
        PlayerRight(&head->player, head->map);
    else if (key == XK_Right)
    {
        printf("pressed ->\n");
        double rot_speed;
        double old_dir_x;
        double old_plane_x;

        rot_speed = 0.1;
        old_dir_x = head->player.dirX;
        head->player.dirX = head->player.dirX * cos(rot_speed) - head->player.dirY * sin(rot_speed);
        head->player.dirY = old_dir_x * sin(rot_speed) + head->player.dirY * cos(rot_speed);
        old_plane_x = head->player.planeX;
        head->player.planeX = head->player.planeX * cos(rot_speed) - head->player.planeY * sin(rot_speed);
        head->player.planeY = old_plane_x * sin(rot_speed) + head->player.planeY * cos(rot_speed);
    }
    else if(key == XK_Left)
    {
        printf("pressed <-\n");
        double rot_speed;
        double old_dir_x;
        double old_plane_x;

        rot_speed = -0.1;
        old_dir_x = head->player.dirX;
        head->player.dirX = head->player.dirX * cos(rot_speed) - head->player.dirY * sin(rot_speed);
        head->player.dirY = old_dir_x * sin(rot_speed) + head->player.dirY * cos(rot_speed);
        old_plane_x = head->player.planeX;
        head->player.planeX = head->player.planeX * cos(rot_speed) - head->player.planeY * sin(rot_speed);
        head->player.planeY = old_plane_x * sin(rot_speed) + head->player.planeY * cos(rot_speed);
    }
    
    Raycaster(head);
    
    return (0);
}
