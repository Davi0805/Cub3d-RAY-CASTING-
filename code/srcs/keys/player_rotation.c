#include "cub3d.h"

/**
 * Rotação de um Vetor em 2D
 * Para rotacionar um vetor (x, y) em um ângulo θ, usamos a matriz de rotação:
 * x′=xcos⁡(θ)−ysin⁡(θ)
 * y′=xsin⁡(θ)+ycos⁡(θ)
 * 
 * The dir plane and the camera plane have to be perpendicular so they both rotate the same
*/

// rotates player and camara right
void PlayerRotateRight(t_player *player)
{
    printf("pressed ->\n");
    double rot_speed = 0.04;
    double temp;

    // player dir plane
    temp = player->dirX;
    player->dirX = player->dirX * cos(rot_speed) - player->dirY * sin(rot_speed);
    player->dirY = temp * sin(rot_speed) + player->dirY * cos(rot_speed);
    // player camera plane
    temp = player->planeX;
    player->planeX = player->planeX * cos(rot_speed) - player->planeY * sin(rot_speed);
    player->planeY = temp * sin(rot_speed) + player->planeY * cos(rot_speed);
}

// rotates player and camara right
void PlayerRotateLeft(t_player *player)
{
    printf("pressed <-\n");
    double rot_speed = -0.04;
    double temp;

    // player dir plane
    temp = player->dirX;
    player->dirX = player->dirX * cos(rot_speed) - player->dirY * sin(rot_speed);
    player->dirY = temp * sin(rot_speed) + player->dirY * cos(rot_speed);
    // player camera plane
    temp = player->planeX;
    player->planeX = player->planeX * cos(rot_speed) - player->planeY * sin(rot_speed);
    player->planeY = temp * sin(rot_speed) + player->planeY * cos(rot_speed);
}
   