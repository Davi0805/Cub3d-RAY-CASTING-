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
        PlayerRotateRight(&head->player);
    else if(key == XK_Left)
        PlayerRotateLeft(&head->player);
    
    Raycaster(head);
    
    return (0);
}
