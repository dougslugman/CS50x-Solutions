#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = (BYTE) round(average);
            image[i][j].rgbtGreen = (BYTE) round(average);
            image[i][j].rgbtBlue = (BYTE) round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            image[i][j].rgbtRed = (BYTE) round(sepiaRed > 255 ? 255 : sepiaRed);
            image[i][j].rgbtGreen = (BYTE) round(sepiaGreen > 255 ? 255 : sepiaGreen);
            image[i][j].rgbtBlue = (BYTE) round(sepiaBlue > 255 ? 255 : sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    float ar, ab, ag;
    int count;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ar = 0;
            ab = 0;
            ag = 0;
            count = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int di = i + k;
                    int dj = j + l;
                    if (di >= 0 && di < height && dj >= 0 && dj < width)
                    {
                        ar += copy[di][dj].rgbtRed;
                        ab += copy[di][dj].rgbtBlue;
                        ag += copy[di][dj].rgbtGreen;

                        count++;
                    }
                }
            }
            ar = ar / count;
            ab = ab / count;
            ag = ag / count;
            image[i][j].rgbtRed = (BYTE) round(ar);
            image[i][j].rgbtBlue = (BYTE) round(ab);
            image[i][j].rgbtGreen = (BYTE) round(ag);
        }
    }
    return;
}
