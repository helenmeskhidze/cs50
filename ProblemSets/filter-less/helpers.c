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
            int gray =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);

            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int remainder = width % 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width - remainder) / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
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

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          4.0);
            }
            // top right corner
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                          4.0);
            }

            // top row
            else if (i == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          6.0);
            }

            // bottom left corner
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                          4.0);
            }

            // bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) /
                          4.0);
            }

            // bottom row
            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                          6.0);
            }

            // left-most column
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          6.0);
            }

            // right-most column
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                          6.0);
            }

            else
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i + 1][j + 1].rgbtRed) /
                                            9.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j + 1].rgbtGreen) /
                          9.0);
                image[i][j].rgbtBlue = round(
                                           (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                            copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                                            copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                            copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                           9.0);
            }
        }
    }
    return;
}
