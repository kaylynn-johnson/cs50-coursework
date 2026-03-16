#include "helpers.h"
#include <math.h>

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
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            // assign the avg to all the RGB values
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
    // loop through half of width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2) + 1; j++)
        {
            // swap j with (width - j)
            // set temp variables (right values)
            temp_blue = image[i][width - j].rgbtBlue;
            temp_green = image[i][width - j].rgbtGreen;
            temp_red = image[i][width - j].rgbtRed;

            // assign right values to left values
            image[i][width - j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j].rgbtRed = image[i][j].rgbtRed;

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
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
