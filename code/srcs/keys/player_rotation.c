#include "cub3d.h"

void PlayerRotateRight(t_player *player)
{
    printf("pressed ->\n");
    double rot_speed;
    double temp;

    rot_speed = 0.1;
    temp = player->dirX;
    player->dirX = player->dirX * cos(rot_speed) - player->dirY * sin(rot_speed);
    player->dirY = temp * sin(rot_speed) + player->dirY * cos(rot_speed);
    temp = player->planeX;
    player->planeX = player->planeX * cos(rot_speed) - player->planeY * sin(rot_speed);
    player->planeY = temp * sin(rot_speed) + player->planeY * cos(rot_speed);
}
void PlayerRotateLeft(t_player *player)
{
    printf("pressed <-\n");
    double rot_speed;
    double temp;

    rot_speed = -0.1;
    temp = player->dirX;
    player->dirX = player->dirX * cos(rot_speed) - player->dirY * sin(rot_speed);
    player->dirY = temp * sin(rot_speed) + player->dirY * cos(rot_speed);
    temp = player->planeX;
    player->planeX = player->planeX * cos(rot_speed) - player->planeY * sin(rot_speed);
    player->planeY = temp * sin(rot_speed) + player->planeY * cos(rot_speed);
}
   