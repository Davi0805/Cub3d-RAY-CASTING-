#include "cub3d.h"

// If possible, updates player x and y position on the map by 
// + MOVESPEED * pDir
void PlayerForward(t_player *player, char **map)
{
    printf("pressed W\n");

    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX + player->dirX * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '0' && map[pMapy][pMapx] != '\n')
        player->posX += player->dirX * MOVESPEED;
    
    // Y axis check
    pMapx = (int)(player->posX);
    pMapy = (int)(player->posY + player->dirY * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '0' && map[pMapy][pMapx] != '\n')
        player->posY += player->dirY * MOVESPEED;
}

// If possible, updates player x and y position on the map by 
// - MOVESPEED * pDir
void PlayerBackword(t_player *player, char **map)
{
    printf("pressed S\n");

    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX - player->dirX * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '\0' && map[pMapy][pMapx] != '\n')
        player->posX -= player->dirX * MOVESPEED;

    // Y axis check
    pMapy = (int)(player->posY - player->dirY * MOVESPEED);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '\0' && map[pMapy][pMapx] != '\n')
        player->posY -= player->dirY * MOVESPEED;
}

// If possible, updates player x and y position on the map by 
// - MOVESPEED * pDir
void PlayerLeft(t_player *player, char **map)
{
    printf("pressed A\n");

    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx = (int)(player->posX - player->planeX * MOVESPEED);
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '\0' && map[pMapy][pMapx] != '\n')
        player->posX -= player->planeX * MOVESPEED;

    // Y axis check
    pMapy = (int)(player->posY - player->planeY * MOVESPEED);
    pMapx = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '\0' && map[pMapy][pMapx] != '\n')
        player->posY -= player->planeY * MOVESPEED;
}

// If possible, updates player x and y position on the map by 
// + MOVESPEED * pDir
void PlayerRight(t_player *player, char **map)
{
    printf("pressed D\n");

    // X axis check
    int pMapy = (int)(player->posY);
    int pMapx =(int)(player->posX + player->planeX * MOVESPEED);
    // if (map[pMapy][pMapx] != '1')
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '\0' && map[pMapy][pMapx] != '\n')
        player->posX += player->planeX * MOVESPEED;

    // Y axis check
    pMapx = (int)(player->posY + player->planeY * MOVESPEED);
    pMapy = (int)(player->posX);
    if (pMapx > 0 && pMapy > 0 &&  map[pMapy] != NULL && map[pMapy][pMapx] != '1' && map[pMapy][pMapx] != '\0' && map[pMapy][pMapx] != '\n')
        player->posY += player->planeY * MOVESPEED;
}
