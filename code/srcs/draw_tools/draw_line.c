#include "cub3d.h"

void DrawLine(t_mlx_data mlx, int x1, int y1, int x2, int y2, int color)
{
    t_dda dda;
    int i;

    dda.dx = x2 - x1;
    dda.dy = y2 - y1;

    // Determina o número de passos necessários (baseado na maior diferença)
    if (abs(dda.dx) > abs(dda.dy))
        dda.steps = abs(dda.dx);
    else
        dda.steps = abs(dda.dy);

    // Calcula os incrementos para cada eixo
    dda.xinc = dda.dx / (float)dda.steps;
    dda.yinc = dda.dy / (float)dda.steps;

    // Inicializa as coordenadas com floats
    dda.x = x1;
    dda.y = y1;

    // Itera pelos passos para desenhar a linha
    i = 0;
    while (i <= dda.steps)
    {
        // Coloca o pixel arredondando as coordenadas
        PutPixelToImg(mlx, (int)(dda.x + 0.49), (int)(dda.y + 0.49), color);

        // Atualiza as coordenadas com os incrementos
        dda.x += dda.xinc;
        dda.y += dda.yinc;

        i++;
    }
}
