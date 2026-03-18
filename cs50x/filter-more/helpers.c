#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // initiate helper variables
    BYTE avg;
    // loop through image by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // average and round the RGB values
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // assign the avg to all the RGB values
            image[i][j].rgbtBlue = (int) avg;
            image[i][j].rgbtGreen = (int) avg;
            image[i][j].rgbtRed = (int) avg;
        }
    }

    return;
}

// Reflect image horizontally (swap left and right)
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // initiate helper variables
    int temp_blue;
    int temp_green;
    int temp_red;
    int halfway;

    if (width % 2 == 0)
    {
        // even width
        halfway = width / 2;
    }
    else
    {
        // odd width
        halfway = width / 2 + 1;
    }
    // loop through half of width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfway; j++)
        {
            // swap j with (width - j)
            // set temp variables (right values)
            temp_blue = image[i][width - j - 1].rgbtBlue;
            temp_green = image[i][width - j - 1].rgbtGreen;
            temp_red = image[i][width - j - 1].rgbtRed;

            // assign right values to left values
            image[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;

            // assign left values to temp variables (right values)
            image[i][j].rgbtBlue = temp_blue;
            image[i][j].rgbtGreen = temp_green;
            image[i][j].rgbtRed = temp_red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // initialize variables
    BYTE avg_blue;
    BYTE avg_green;
    BYTE avg_red;
    RGBTRIPLE temp_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Determine pixels to average
            if (i == 0 && j == 0)
            {
                // top left corner
                avg_blue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                  image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                                 4.0);
                avg_green = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                   image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                                  4.0);
                avg_red = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                                4.0);
            }
            else if (i == 0 && j == (width - 1))
            {
                // top right corner
                avg_blue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                  image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) /
                                 4.0);
                avg_green = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                   image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                                  4.0);
                avg_red = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                                 image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) /
                                4.0);
            }
            else if (i == (height - 1) && j == 0)
            {
                // bottom left corner
                avg_blue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                  image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) /
                                 4.0);
                avg_green = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                   image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) /
                                  4.0);
                avg_red = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                 image[i][j].rgbtRed + image[i][j + 1].rgbtRed) /
                                4.0);
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                // bottom right corner
                avg_blue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                  image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue) /
                                 4.0);
                avg_green = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                   image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen) /
                                  4.0);
                avg_red = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                 image[i][j - 1].rgbtRed + image[i][j].rgbtRed) /
                                4.0);
            }
            else if (j == 0)
            {
                // left side
                avg_blue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                  image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                  image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                                 6.0);
                avg_green = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                   image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                   image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                                  6.0);
                avg_red = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                 image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                                6.0);
            }
            else if (j == (width - 1))
            {
                // right side
                avg_blue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                  image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                  image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) /
                                 6.0);
                avg_green = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                   image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                   image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                                  6.0);
                avg_red = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                 image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                                 image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) /
                                6.0);
            }
            else if (i == 0)
            {
                // top side
                avg_blue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                  image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                  image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                                 6.0);
                avg_green = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                   image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                   image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                                  6.0);
                avg_red = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                                 image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                                6.0);
            }
            else if (i == (height - 1))
            {
                // bottom side
                avg_blue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                  image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                  image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) /
                                 6.0);
                avg_green = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                   image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                   image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) /
                                  6.0);
                avg_red = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                 image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                                 image[i][j].rgbtRed + image[i][j + 1].rgbtRed) /
                                6.0);
            }
            else
            {
                // middle pixel
                avg_blue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                  image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                  image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                  image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                  image[i + 1][j + 1].rgbtBlue) /
                                 9.0);
                avg_green = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                   image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                   image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                   image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                   image[i + 1][j + 1].rgbtGreen) /
                                  9.0);
                avg_red = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                 image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                                 image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                 image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                 image[i + 1][j + 1].rgbtRed) /
                                9.0);
            }
            // assign the avg to all the RGB values for temp_image as to not overwrite values in
            // image
            temp_image[i][j].rgbtBlue = (int) avg_blue;
            temp_image[i][j].rgbtGreen = (int) avg_green;
            temp_image[i][j].rgbtRed = (int) avg_red;
        }
    }

    // Reassign temp_image to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp_image[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // initialize variables
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    LONG new_blue;
    LONG new_green;
    LONG new_red;
    LONG gx_blue;
    LONG gy_blue;
    LONG gx_green;
    LONG gy_green;
    LONG gx_red;
    LONG gy_red;
    RGBTRIPLE temp_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Determine pixels to weight average
            if (i == 0 && j == 0)
            {
                // top left corner
                // determine blue kernels
                gx_blue = (Gx[1][1] * image[i][j].rgbtBlue) +
                          (Gx[1][2] * image[i][j + 1].rgbtBlue) +
                          (Gx[2][1] * image[i + 1][j].rgbtBlue) +
                          (Gx[2][2] * image[i + 1][j + 1].rgbtBlue);
                gy_blue = (Gy[1][1] * image[i][j].rgbtBlue) +
                          (Gy[1][2] * image[i][j + 1].rgbtBlue) +
                          (Gy[2][1] * image[i + 1][j].rgbtBlue) +
                          (Gy[2][2] * image[i + 1][j + 1].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gx[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gx[2][2] * image[i + 1][j + 1].rgbtGreen);
                gy_green = (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gy[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gy[2][2] * image[i + 1][j + 1].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[1][1] * image[i][j].rgbtRed) + (Gx[1][2] * image[i][j + 1].rgbtRed) +
                         (Gx[2][1] * image[i + 1][j].rgbtRed) +
                         (Gx[2][2] * image[i + 1][j + 1].rgbtRed);
                gy_red = (Gy[1][1] * image[i][j].rgbtRed) + (Gy[1][2] * image[i][j + 1].rgbtRed) +
                         (Gy[2][1] * image[i + 1][j].rgbtRed) +
                         (Gy[2][2] * image[i + 1][j + 1].rgbtRed);
            }
            else if (i == 0 && j == (width - 1))
            {
                // top right corner
                // determine blue kernels
                gx_blue = (Gx[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gx[1][1] * image[i][j].rgbtBlue) +
                          (Gx[2][0] * image[i + 1][j - 1].rgbtBlue) +
                          (Gx[2][1] * image[i + 1][j].rgbtBlue);
                gy_blue = (Gy[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gy[1][1] * image[i][j].rgbtBlue) +
                          (Gy[2][0] * image[i + 1][j - 1].rgbtBlue) +
                          (Gy[2][1] * image[i + 1][j].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gx[2][1] * image[i + 1][j].rgbtGreen);
                gy_green = (Gy[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gy[2][1] * image[i + 1][j].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[1][0] * image[i][j - 1].rgbtRed) + (Gx[1][1] * image[i][j].rgbtRed) +
                         (Gx[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gx[2][1] * image[i + 1][j].rgbtRed);
                gy_red = (Gy[1][0] * image[i][j - 1].rgbtRed) + (Gy[1][1] * image[i][j].rgbtRed) +
                         (Gy[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gy[2][1] * image[i + 1][j].rgbtRed);
            }
            else if (i == (height - 1) && j == 0)
            {
                // bottom left corner
                // determine blue kernels
                gx_blue = (Gx[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gx[0][2] * image[i - 1][j + 1].rgbtBlue) +
                          (Gx[1][1] * image[i][j].rgbtBlue) + (Gx[1][2] * image[i][j + 1].rgbtBlue);
                gy_blue = (Gy[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gy[0][2] * image[i - 1][j + 1].rgbtBlue) +
                          (Gy[1][1] * image[i][j].rgbtBlue) + (Gy[1][2] * image[i][j + 1].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gx[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[1][2] * image[i][j + 1].rgbtGreen);
                gy_green = (Gy[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gy[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[1][2] * image[i][j + 1].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[0][1] * image[i - 1][j].rgbtRed) +
                         (Gx[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gx[1][1] * image[i][j].rgbtRed) + (Gx[1][2] * image[i][j + 1].rgbtRed);
                gy_red = (Gy[0][1] * image[i - 1][j].rgbtRed) +
                         (Gy[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gy[1][1] * image[i][j].rgbtRed) + (Gy[1][2] * image[i][j + 1].rgbtRed);
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                // bottom right corner
                // determine blue kermels
                gx_blue = (Gx[0][0] * image[i - 1][j - 1].rgbtBlue) +
                          (Gx[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gx[1][0] * image[i][j - 1].rgbtBlue) + (Gx[1][1] * image[i][j].rgbtBlue);
                gy_blue = (Gy[0][0] * image[i - 1][j - 1].rgbtBlue) +
                          (Gy[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gy[1][0] * image[i][j - 1].rgbtBlue) + (Gy[1][1] * image[i][j].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gx[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gx[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen);
                gy_green = (Gy[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gy[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gy[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gx[0][1] * image[i - 1][j].rgbtRed) +
                         (Gx[1][0] * image[i][j - 1].rgbtRed) + (Gx[1][1] * image[i][j].rgbtRed);
                gy_red = (Gy[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gy[0][1] * image[i - 1][j].rgbtRed) +
                         (Gy[1][0] * image[i][j - 1].rgbtRed) + (Gy[1][1] * image[i][j].rgbtRed);
            }
            else if (j == 0)
            {
                // left side
                // determine blue kernels
                gx_blue =
                    (Gx[0][1] * image[i - 1][j].rgbtBlue) +
                    (Gx[0][2] * image[i - 1][j + 1].rgbtBlue) + (Gx[1][1] * image[i][j].rgbtBlue) +
                    (Gx[1][2] * image[i][j + 1].rgbtBlue) + (Gx[2][1] * image[i + 1][j].rgbtBlue) +
                    (Gx[2][2] * image[i + 1][j + 1].rgbtBlue);
                gy_blue =
                    (Gy[0][1] * image[i - 1][j].rgbtBlue) +
                    (Gy[0][2] * image[i - 1][j + 1].rgbtBlue) + (Gy[1][1] * image[i][j].rgbtBlue) +
                    (Gy[1][2] * image[i][j + 1].rgbtBlue) + (Gy[2][1] * image[i + 1][j].rgbtBlue) +
                    (Gy[2][2] * image[i + 1][j + 1].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gx[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gx[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gx[2][2] * image[i + 1][j + 1].rgbtGreen);
                gy_green = (Gy[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gy[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gy[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gy[2][2] * image[i + 1][j + 1].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[0][1] * image[i - 1][j].rgbtRed) +
                         (Gx[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gx[1][1] * image[i][j].rgbtRed) + (Gx[1][2] * image[i][j + 1].rgbtRed) +
                         (Gx[2][1] * image[i + 1][j].rgbtRed) +
                         (Gx[2][2] * image[i + 1][j + 1].rgbtRed);
                gy_red = (Gy[0][1] * image[i - 1][j].rgbtRed) +
                         (Gy[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gy[1][1] * image[i][j].rgbtRed) + (Gy[1][2] * image[i][j + 1].rgbtRed) +
                         (Gy[2][1] * image[i + 1][j].rgbtRed) +
                         (Gy[2][2] * image[i + 1][j + 1].rgbtRed);
            }
            else if (j == (width - 1))
            {
                // right side
                // determine blue kernels
                gx_blue =
                    (Gx[0][0] * image[i - 1][j - 1].rgbtBlue) +
                    (Gx[0][1] * image[i - 1][j].rgbtBlue) + (Gx[1][0] * image[i][j - 1].rgbtBlue) +
                    (Gx[1][1] * image[i][j].rgbtBlue) + (Gx[2][0] * image[i + 1][j - 1].rgbtBlue) +
                    (Gx[2][1] * image[i + 1][j].rgbtBlue);
                gy_blue =
                    (Gy[0][0] * image[i - 1][j - 1].rgbtBlue) +
                    (Gy[0][1] * image[i - 1][j].rgbtBlue) + (Gy[1][0] * image[i][j - 1].rgbtBlue) +
                    (Gy[1][1] * image[i][j].rgbtBlue) + (Gy[2][0] * image[i + 1][j - 1].rgbtBlue) +
                    (Gy[2][1] * image[i + 1][j].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gx[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gx[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gx[2][1] * image[i + 1][j].rgbtGreen);
                gy_green = (Gy[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gy[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gy[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gy[2][1] * image[i + 1][j].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gx[0][1] * image[i - 1][j].rgbtRed) +
                         (Gx[1][0] * image[i][j - 1].rgbtRed) + (Gx[1][1] * image[i][j].rgbtRed) +
                         (Gx[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gx[2][1] * image[i + 1][j].rgbtRed);
                gy_red = (Gy[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gy[0][1] * image[i - 1][j].rgbtRed) +
                         (Gy[1][0] * image[i][j - 1].rgbtRed) + (Gy[1][1] * image[i][j].rgbtRed) +
                         (Gy[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gy[2][1] * image[i + 1][j].rgbtRed);
            }
            else if (i == 0)
            {
                // top side
                // determine blue kernels
                gx_blue = (Gx[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gx[1][1] * image[i][j].rgbtBlue) +
                          (Gx[1][2] * image[i][j + 1].rgbtBlue) +
                          (Gx[2][0] * image[i + 1][j - 1].rgbtBlue) +
                          (Gx[2][1] * image[i + 1][j].rgbtBlue) +
                          (Gx[2][2] * image[i + 1][j + 1].rgbtBlue);
                gy_blue = (Gy[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gy[1][1] * image[i][j].rgbtBlue) +
                          (Gy[1][2] * image[i][j + 1].rgbtBlue) +
                          (Gy[2][0] * image[i + 1][j - 1].rgbtBlue) +
                          (Gy[2][1] * image[i + 1][j].rgbtBlue) +
                          (Gy[2][2] * image[i + 1][j + 1].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gx[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gx[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gx[2][2] * image[i + 1][j + 1].rgbtGreen);
                gy_green = (Gy[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gy[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gy[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gy[2][2] * image[i + 1][j + 1].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[1][0] * image[i][j - 1].rgbtRed) + (Gx[1][1] * image[i][j].rgbtRed) +
                         (Gx[1][2] * image[i][j + 1].rgbtRed) +
                         (Gx[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gx[2][1] * image[i + 1][j].rgbtRed) +
                         (Gx[2][2] * image[i + 1][j + 1].rgbtRed);
                gy_red = (Gy[1][0] * image[i][j - 1].rgbtRed) + (Gy[1][1] * image[i][j].rgbtRed) +
                         (Gy[1][2] * image[i][j + 1].rgbtRed) +
                         (Gy[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gy[2][1] * image[i + 1][j].rgbtRed) +
                         (Gy[2][2] * image[i + 1][j + 1].rgbtRed);
            }
            else if (i == (height - 1))
            {
                // bottom side
                // determine blue kernels
                gx_blue = (Gx[0][0] * image[i - 1][j - 1].rgbtBlue) +
                          (Gx[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gx[0][2] * image[i - 1][j + 1].rgbtBlue) +
                          (Gx[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gx[1][1] * image[i][j].rgbtBlue) + (Gx[1][2] * image[i][j + 1].rgbtBlue);
                gy_blue = (Gy[0][0] * image[i - 1][j - 1].rgbtBlue) +
                          (Gy[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gy[0][2] * image[i - 1][j + 1].rgbtBlue) +
                          (Gy[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gy[1][1] * image[i][j].rgbtBlue) + (Gy[1][2] * image[i][j + 1].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gx[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gx[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gx[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[1][2] * image[i][j + 1].rgbtGreen);
                gy_green = (Gy[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gy[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gy[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gy[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[1][2] * image[i][j + 1].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gx[0][1] * image[i - 1][j].rgbtRed) +
                         (Gx[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gx[1][0] * image[i][j - 1].rgbtRed) + (Gx[1][1] * image[i][j].rgbtRed) +
                         (Gx[1][2] * image[i][j + 1].rgbtRed);
                gy_red = (Gy[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gy[0][1] * image[i - 1][j].rgbtRed) +
                         (Gy[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gy[1][0] * image[i][j - 1].rgbtRed) + (Gy[1][1] * image[i][j].rgbtRed) +
                         (Gy[1][2] * image[i][j + 1].rgbtRed);
            }
            else
            {
                // middle pixel
                // determine blue kernels
                gx_blue = (Gx[0][0] * image[i - 1][j - 1].rgbtBlue) +
                          (Gx[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gx[0][2] * image[i - 1][j + 1].rgbtBlue) +
                          (Gx[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gx[1][1] * image[i][j].rgbtBlue) +
                          (Gx[1][2] * image[i][j + 1].rgbtBlue) +
                          (Gx[2][0] * image[i + 1][j - 1].rgbtBlue) +
                          (Gx[2][1] * image[i + 1][j].rgbtBlue) +
                          (Gx[2][2] * image[i + 1][j + 1].rgbtBlue);
                gy_blue = (Gy[0][0] * image[i - 1][j - 1].rgbtBlue) +
                          (Gy[0][1] * image[i - 1][j].rgbtBlue) +
                          (Gy[0][2] * image[i - 1][j + 1].rgbtBlue) +
                          (Gy[1][0] * image[i][j - 1].rgbtBlue) +
                          (Gy[1][1] * image[i][j].rgbtBlue) +
                          (Gy[1][2] * image[i][j + 1].rgbtBlue) +
                          (Gy[2][0] * image[i + 1][j - 1].rgbtBlue) +
                          (Gy[2][1] * image[i + 1][j].rgbtBlue) +
                          (Gy[2][2] * image[i + 1][j + 1].rgbtBlue);

                // determine green kernels
                gx_green = (Gx[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gx[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gx[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gx[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gx[1][1] * image[i][j].rgbtGreen) +
                           (Gx[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gx[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gx[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gx[2][2] * image[i + 1][j + 1].rgbtGreen);
                gy_green = (Gy[0][0] * image[i - 1][j - 1].rgbtGreen) +
                           (Gy[0][1] * image[i - 1][j].rgbtGreen) +
                           (Gy[0][2] * image[i - 1][j + 1].rgbtGreen) +
                           (Gy[1][0] * image[i][j - 1].rgbtGreen) +
                           (Gy[1][1] * image[i][j].rgbtGreen) +
                           (Gy[1][2] * image[i][j + 1].rgbtGreen) +
                           (Gy[2][0] * image[i + 1][j - 1].rgbtGreen) +
                           (Gy[2][1] * image[i + 1][j].rgbtGreen) +
                           (Gy[2][2] * image[i + 1][j + 1].rgbtGreen);

                // determine red kernels
                gx_red = (Gx[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gx[0][1] * image[i - 1][j].rgbtRed) +
                         (Gx[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gx[1][0] * image[i][j - 1].rgbtRed) + (Gx[1][1] * image[i][j].rgbtRed) +
                         (Gx[1][2] * image[i][j + 1].rgbtRed) +
                         (Gx[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gx[2][1] * image[i + 1][j].rgbtRed) +
                         (Gx[2][2] * image[i + 1][j + 1].rgbtRed);
                gy_red = (Gy[0][0] * image[i - 1][j - 1].rgbtRed) +
                         (Gy[0][1] * image[i - 1][j].rgbtRed) +
                         (Gy[0][2] * image[i - 1][j + 1].rgbtRed) +
                         (Gy[1][0] * image[i][j - 1].rgbtRed) + (Gy[1][1] * image[i][j].rgbtRed) +
                         (Gy[1][2] * image[i][j + 1].rgbtRed) +
                         (Gy[2][0] * image[i + 1][j - 1].rgbtRed) +
                         (Gy[2][1] * image[i + 1][j].rgbtRed) +
                         (Gy[2][2] * image[i + 1][j + 1].rgbtRed);
            }

            new_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
            new_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            new_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            // assign to temp image and cap at 255
            if (new_blue > 255)
            {
                temp_image[i][j].rgbtBlue = 255;
            }
            else
            {
                temp_image[i][j].rgbtBlue = (int) new_blue;
            }

            if (new_green > 255)
            {
                temp_image[i][j].rgbtGreen = 255;
            }
            else
            {
                temp_image[i][j].rgbtGreen = (int) new_green;
            }

            if (new_red > 255)
            {
                temp_image[i][j].rgbtRed = 255;
            }
            else
            {
                temp_image[i][j].rgbtRed = (int) new_red;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp_image[i][j].rgbtRed;
        }
    }
    return;
}
