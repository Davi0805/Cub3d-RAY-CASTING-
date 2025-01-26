#include "cub3d.h"

// If possible, updates player x and y position on the map by 
// + MOVESPEED * pDir
void PlayerForward(t_player *player, char **map, t_cub *head)
{

    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX + player->dirX * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posX += player->dirX * MOVESPEED;
    // Y axis check
    pMapx = (int)(player->posX);
    pMapy = (int)(player->posY + player->dirY * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
        player->posY += player->dirY * MOVESPEED;
}

// If possible, updates player x and y position on the map by 
// - MOVESPEED * pDir
void PlayerBackward(t_player *player, char **map, t_cub *head)
{
    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX - player->dirX * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
        player->posX -= player->dirX * MOVESPEED;
    // Y axis check
    pMapy = (int)(player->posY - player->dirY * MOVESPEED);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posY -= player->dirY * MOVESPEED;
}

// If possible, updates player x and y position on the map by 
// - MOVESPEED * pDir
void PlayerLeft(t_player *player, char **map, t_cub *head)
{
    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX - player->planeX * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posX -= player->planeX * MOVESPEED;
    // Y axis check
    pMapy = (int)(player->posY - player->planeY * MOVESPEED);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posY -= player->planeY * MOVESPEED;
}

// If possible, updates player x and y position on the map by 
// + MOVESPEED * pDir
void PlayerRight(t_player *player, char **map, t_cub *head)
{
    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx =(int)(player->posX + player->planeX * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posX += player->planeX * MOVESPEED;
    // Y axis check
    pMapy = (int)(player->posY + player->planeY * MOVESPEED);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posY += player->planeY * MOVESPEED;
}
