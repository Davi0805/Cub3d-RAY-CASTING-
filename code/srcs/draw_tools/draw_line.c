#include "cub3d.h"

// DDA line draw algorithm
// Draws a line starting at (x1,y1) and ending at (x2,y2) with color <color>
void DrawLine(t_mlx_data mlx, int x1, int y1, int x2, int y2, int color)
{
    t_dda dda;
    int i;

    dda.dx = x2 - x1;
    dda.dy = y2 - y1;

    // How many steps (biggest)
    if (abs(dda.dx) > abs(dda.dy))
        dda.steps = abs(dda.dx);
    else
        dda.steps = abs(dda.dy);

    // Calculate increments
    dda.xinc = dda.dx / (float)dda.steps;
    dda.yinc = dda.dy / (float)dda.steps;

    // to floats
    dda.x = x1;
    dda.y = y1;
    // Line drawing
    i = 0;
    while (i <= dda.steps)
    {
        // Draws the pixel and rounds it cuz floats
        PutPixelToImg(mlx, (int)(dda.x + 0.5), (int)(dda.y + 0.5), color);

        // Next pixel
        dda.x += dda.xinc;
        dda.y += dda.yinc;

        // Next step
        i++;
    }
}
