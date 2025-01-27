#include "cub3d.h"

// If possible, updates player x and y position on the map by 
// + head->deltaTime * pDir
void PlayerForward(t_player *player, char **map, t_cub *head)
{

    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX + player->dirX * MOVESPEED * head->deltaTime);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posX += player->dirX * MOVESPEED * head->deltaTime;
    // Y axis check
    pMapx = (int)(player->posX);
    pMapy = (int)(player->posY + player->dirY * MOVESPEED * head->deltaTime);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
        player->posY += player->dirY * MOVESPEED * head->deltaTime;
}

// If possible, updates player x and y position on the map by 
// - head->deltaTime * pDir
void PlayerBackward(t_player *player, char **map, t_cub *head)
{
    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX - player->dirX * MOVESPEED * head->deltaTime);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
        player->posX -= player->dirX * MOVESPEED * head->deltaTime;
    // Y axis check
    pMapy = (int)(player->posY - player->dirY * MOVESPEED * head->deltaTime);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posY -= player->dirY * MOVESPEED * head->deltaTime;
}

// If possible, updates player x and y position on the map by 
// - head->deltaTime * pDir
void PlayerLeft(t_player *player, char **map, t_cub *head)
{
    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX - player->planeX * MOVESPEED * head->deltaTime);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posX -= player->planeX * MOVESPEED * head->deltaTime;
    // Y axis check
    pMapy = (int)(player->posY - player->planeY * MOVESPEED * head->deltaTime);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posY -= player->planeY * MOVESPEED * head->deltaTime;
}

// If possible, updates player x and y position on the map by 
// + head->deltaTime * pDir
void PlayerRight(t_player *player, char **map, t_cub *head)
{
    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx =(int)(player->posX + player->planeX * head->deltaTime);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posX += player->planeX * head->deltaTime;
    // Y axis check
    pMapy = (int)(player->posY + player->planeY * head->deltaTime);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 // less than 0
     && pMapy < head->mapHeight && pMapx < head->mapLineLens[pMapy] // more than map len 
     && map[pMapy][(int)(pMapx)] != '1')
            player->posY += player->planeY * head->deltaTime;
}
