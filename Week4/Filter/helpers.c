#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loops through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Averages the RGB values of the pixel
            RGBTRIPLE curr_pixel = image[i][j];
            float average = round((curr_pixel.rgbtRed + curr_pixel.rgbtGreen + curr_pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int size_line = sizeof(RGBTRIPLE) * width;
    // Loops through every line of pixels
    for (int i = 0; i < height; i++)
    {
        // Memory allocation for the reversed line of pixels
        RGBTRIPLE *temp_line = malloc(size_line);
        // Looping through every pixel in the line and storing in reverse order
        for (int j = 0; j < width; j++)
        {
            *(temp_line + width - 1 - j) = image[i][j];
        }
        // Overwrite the original line with the reversed one
        memcpy(image[i], temp_line, size_line);
        free(temp_line);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    // Creates a copy of the image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            original[h][w] = image[h][w];
        }
    }
    // Loops through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg_rgb[3] = {0.0, 0.0, 0.0};
            int valid_px = 0;
            int box_i[3][3] =
            {
                {i - 1, i - 1, i - 1},
                {i, i, i},
                {i + 1, i + 1, i + 1}
            };
            int box_j[3][3] =
            {
                {j - 1, j, j + 1},
                {j - 1, j, j + 1},
                {j - 1, j, j + 1}
            };
            // Loops through every pixel in the 3x3 box
            for (int ii = 0; ii < 3; ii++)
            {
                for (int jj = 0; jj < 3; jj++)
                {
                    // Checking if the index is inside the image
                    if (box_i[ii][jj] >= 0 && box_i[ii][jj] < height && box_j[ii][jj] >= 0 && box_j[ii][jj] < width)
                    {
                        int id_x = box_i[ii][jj];
                        int id_y = box_j[ii][jj];

                        avg_rgb[0] += (float) original[id_x][id_y].rgbtRed;
                        avg_rgb[1] += (float) original[id_x][id_y].rgbtGreen;
                        avg_rgb[2] += (float) original[id_x][id_y].rgbtBlue;
                        valid_px++;
                    }
                }
            }
            // Dividing by the number of valid pixels found in the box to compute the average
            avg_rgb[0] /= valid_px;
            avg_rgb[1] /= valid_px;
            avg_rgb[2] /= valid_px;

            image[i][j].rgbtRed = (int) round(avg_rgb[0]);
            image[i][j].rgbtGreen = (int) round(avg_rgb[1]);
            image[i][j].rgbtBlue = (int) round(avg_rgb[2]);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE original[height][width];
    // Creates a copy of the image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            original[h][w] = image[h][w];
        }
    }
    // Initializing the Sobel operators
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    // Loops through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_rgb[3] = {0.0, 0.0, 0.0};
            float Gy_rgb[3] = {0.0, 0.0, 0.0};
            float G_rgb[3] = {0.0, 0.0, 0.0};
            int box_i[3][3] =
            {
                {i - 1, i - 1, i - 1},
                {i, i, i},
                {i + 1, i + 1, i + 1}
            };
            int box_j[3][3] =
            {
                {j - 1, j, j + 1},
                {j - 1, j, j + 1},
                {j - 1, j, j + 1}
            };
            // Loops through every pixel in the 3x3 box
            for (int ii = 0; ii < 3; ii++)
            {
                for (int jj = 0; jj < 3; jj++)
                {
                    // Checking if the index is inside the image
                    if (box_i[ii][jj] >= 0 && box_i[ii][jj] < height && box_j[ii][jj] >= 0 && box_j[ii][jj] < width)
                    {
                        int id_x = box_i[ii][jj];
                        int id_y = box_j[ii][jj];

                        Gx_rgb[0] += (float) original[id_x][id_y].rgbtRed * Gx[ii][jj];
                        Gx_rgb[1] += (float) original[id_x][id_y].rgbtGreen * Gx[ii][jj];
                        Gx_rgb[2] += (float) original[id_x][id_y].rgbtBlue * Gx[ii][jj];

                        Gy_rgb[0] += (float) original[id_x][id_y].rgbtRed * Gy[ii][jj];
                        Gy_rgb[1] += (float) original[id_x][id_y].rgbtGreen * Gy[ii][jj];
                        Gy_rgb[2] += (float) original[id_x][id_y].rgbtBlue * Gy[ii][jj];
                    }
                }
            }
            // Combines Gx and Gy
            G_rgb[0] = sqrt((Gx_rgb[0] * Gx_rgb[0]) + (Gy_rgb[0] * Gy_rgb[0]));
            G_rgb[1] = sqrt((Gx_rgb[1] * Gx_rgb[1]) + (Gy_rgb[1] * Gy_rgb[1]));
            G_rgb[2] = sqrt((Gx_rgb[2] * Gx_rgb[2]) + (Gy_rgb[2] * Gy_rgb[2]));
            // For each channel, prevents an integer overflow from happening by capping the value at 255
            for (int px = 0; px < 3; px++)
            {
                if (G_rgb[px] > 255)
                {
                    G_rgb[px] = 255;
                }
            }

            image[i][j].rgbtRed = (int) round(G_rgb[0]);
            image[i][j].rgbtGreen = (int) round(G_rgb[1]);
            image[i][j].rgbtBlue = (int) round(G_rgb[2]);
        }
    }
    return;
}
