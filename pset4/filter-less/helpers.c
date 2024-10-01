#include <math.h>
#include <stdbool.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Take average of red, green, and blue
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int blue = image[h][w].rgbtBlue;
            int grey = round((red + green + blue) / 3.0);

            // Update pixel values
            image[h][w].rgbtRed = (BYTE) grey;
            image[h][w].rgbtGreen = (BYTE) grey;
            image[h][w].rgbtBlue = (BYTE) grey;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Compute sepia values
            int originalRed = image[h][w].rgbtRed;
            int originalGreen = image[h][w].rgbtGreen;
            int originalBlue = image[h][w].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Update pixel with sepia values
            image[h][w].rgbtRed = (BYTE) (sepiaRed > 255) ? 255 : sepiaRed;
            image[h][w].rgbtGreen = (BYTE) (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[h][w].rgbtBlue = (BYTE) (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++) // loop half of width
        {
            // Swap pixels
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - w - 1]; // -1 as len is size-1
            image[h][width - w - 1] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop over all pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++) // loop half of width
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            double pixels = 0;

            // To iterate through pixels
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    // Check edge cases for height
                    if (h + r < 0 || h + r > height-1)
                    {
                        continue;
                    }
                    // Check edge cases for width
                    if (w + c < 0 || w + c > width-1)
                    {
                        continue;
                    }
                    // Summation of pixel and its surroundings
                    sumRed += copy[h+r][w+c].rgbtRed;
                    sumGreen += copy[h+r][w+c].rgbtGreen;
                    sumBlue += copy[h+r][w+c].rgbtBlue;
                    pixels += 1;

                    // Update pixel with blur values
                    image[h][w].rgbtRed = (BYTE) round(sumRed/pixels);
                    image[h][w].rgbtGreen = (BYTE) round(sumGreen/pixels);
                    image[h][w].rgbtBlue = (BYTE) round(sumBlue/pixels);
                }
            }
        }
    }

    return;
}
