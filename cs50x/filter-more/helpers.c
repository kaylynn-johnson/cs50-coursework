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
    BYTE avg_blue;
    BYTE avg_green;
    BYTE avg_red;
    float num_pixels;
    //int pixels[12];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Determine pixels to average
            if (i == 0 && j == 0)
            {
                // top left corner
                avg_blue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue
                                + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 4.0);
                avg_green = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen
                                + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 4.0);
                avg_red = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed
                                + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 4.0);
            }
            else if (i == 0 && j == (width - 1))
            {
                // top right corner
                avg_blue = round((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue
                                + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue) / 4.0);
                avg_green = round((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen
                                + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen) / 4.0);
                avg_red = round((image[i][j-1].rgbtRed + image[i][j].rgbtRed
                                + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed) / 4.0);
            }
            else if (i == (height - 1) && j == 0)
            {
                // bottom left corner
                avg_blue = round((image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue
                                + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue) / 4.0);
                avg_green = round((image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen
                                + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen) / 4.0);
                avg_red = round((image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed
                                + image[i][j].rgbtRed + image[i][j+1].rgbtRed) / 4.0);
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                // bottom right corner
                avg_blue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue
                                + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
                avg_green = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen
                                + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                avg_red = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed
                                + image[i][j-1].rgbtRed + image[i][j].rgbtRed) / 4.0);
            }
            else if (j == 0)
            {
                // left side
                avg_blue = round((image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                          image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                          image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);
                avg_green = round((image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                          image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                          image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                avg_red = round((image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                          image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                          image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
            }
            else if (j == (width - 1))
            {
                // right side
                avg_blue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue +
                          image[i][j-1].rgbtBlue + image[i][j].rgbtBlue +
                          image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue) / 6.0);
                avg_green = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen +
                          image[i][j-1].rgbtGreen + image[i][j].rgbtGreen +
                          image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen) / 6.0);
                avg_red = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed +
                          image[i][j-1].rgbtRed + image[i][j].rgbtRed +
                          image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed) / 6.0);
            }
            else if (i == 0)
            {
                // top side
                avg_blue = round((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);
                avg_green = round((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                avg_red = round((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
            }
            else if (i == (height - 1))
            {
                // bottom side
                avg_blue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                                image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue) / 6.0);
                avg_green = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                                image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen) / 6.0);
                avg_red = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                                image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed) / 6.0);
            }
            else
            {
                // middle pixel
                avg_blue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                                image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 12.0);
                avg_green = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                                image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 12.0);
                avg_red = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                                image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 12.0);
            }

            // assign the avg to all the RGB values
            image[i][j].rgbtBlue = (int) avg_blue;
            image[i][j].rgbtGreen = (int) avg_green;
            image[i][j].rgbtRed = (int) avg_red;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
