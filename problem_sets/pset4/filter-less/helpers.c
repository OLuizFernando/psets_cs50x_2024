#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avarage;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avarage =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = avarage;
            image[i][j].rgbtGreen = avarage;
            image[i][j].rgbtBlue = avarage;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) +
                             (image[i][j].rgbtBlue * 0.189));
            sepiaGreen = round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) +
                               (image[i][j].rgbtBlue * 0.168));
            sepiaBlue = round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) +
                              (image[i][j].rgbtBlue * 0.131));

            while (sepiaRed > 255)
            {
                sepiaRed--;
            }

            while (sepiaGreen > 255)
            {
                sepiaGreen--;
            }

            while (sepiaBlue > 255)
            {
                sepiaBlue--;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflected_row[width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            reflected_row[j] = image[i][width - (j + 1)];
        }

        for (int k = 0; k < width; k++)
        {
            image[i][k] = reflected_row[k];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred_image[height][width];
    float avarageRed, avarageGreen, avarageBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner
            if (i == 0 && j == 0)
            {
                avarageRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                              image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                             4.0;

                avarageGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                               4.0;

                avarageBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                               image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                              4.0;
            }
            // Top right corner
            else if (i == 0 && j == width - 1)
            {
                avarageRed = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                              image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) /
                             4.0;

                avarageGreen = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) /
                               4.0;

                avarageBlue = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                               image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) /
                              4.0;
            }
            // Lower left corner
            else if (i == height - 1 && j == 0)
            {
                avarageRed = (image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                              image[i][j].rgbtRed + image[i][j + 1].rgbtRed) /
                             4.0;

                avarageGreen = (image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) /
                               4.0;

                avarageBlue = (image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                               image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) /
                              4.0;
            }
            // Lower right corner
            else if (i == height - 1 && j == width - 1)
            {
                avarageRed = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                              image[i][j - 1].rgbtRed + image[i][j].rgbtRed) /
                             4.0;

                avarageGreen = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen) /
                               4.0;

                avarageBlue = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                               image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue) /
                              4.0;
            }
            // Top edge
            else if (i == 0)
            {
                avarageRed =
                    image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;

                avarageRed += image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                              image[i + 1][j + 1].rgbtRed;

                avarageRed /= 6.0;

                avarageGreen =
                    image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;

                avarageGreen += image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                image[i + 1][j + 1].rgbtGreen;

                avarageGreen /= 6.0;

                avarageBlue =
                    image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;

                avarageBlue += image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                               image[i + 1][j + 1].rgbtBlue;

                avarageBlue /= 6.0;
            }
            // Left edge
            else if (j == 0)
            {
                avarageRed =
                    image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed;

                avarageRed +=
                    image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;

                avarageRed /= 6.0;

                avarageGreen = image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                               image[i][j].rgbtGreen;

                avarageGreen += image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                image[i + 1][j + 1].rgbtGreen;

                avarageGreen /= 6.0;

                avarageBlue =
                    image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue;

                avarageBlue += image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                               image[i + 1][j + 1].rgbtBlue;

                avarageBlue /= 6.0;
            }
            // Right edge
            else if (j == width - 1)
            {
                avarageRed =
                    image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed;

                avarageRed +=
                    image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;

                avarageRed /= 6.0;

                avarageGreen = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                               image[i][j - 1].rgbtGreen;

                avarageGreen += image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                image[i + 1][j].rgbtGreen;

                avarageGreen /= 6.0;

                avarageBlue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                              image[i][j - 1].rgbtBlue;

                avarageBlue +=
                    image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;

                avarageBlue /= 6.0;
            }
            // Bottom edge
            else if (i == height - 1)
            {
                avarageRed = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                             image[i - 1][j + 1].rgbtRed;

                avarageRed +=
                    image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;

                avarageRed /= 6.0;

                avarageGreen = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                               image[i - 1][j + 1].rgbtGreen;

                avarageGreen +=
                    image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;

                avarageGreen /= 6.0;

                avarageBlue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                              image[i - 1][j + 1].rgbtBlue;

                avarageBlue +=
                    image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;

                avarageBlue /= 6.0;
            }
            // Middle
            else
            {
                avarageRed = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                             image[i - 1][j + 1].rgbtRed;

                avarageRed +=
                    image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;

                avarageRed += image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                              image[i + 1][j + 1].rgbtRed;

                avarageRed /= 9.0;

                avarageGreen = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                               image[i - 1][j + 1].rgbtGreen;

                avarageGreen +=
                    image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;

                avarageGreen += image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                image[i + 1][j + 1].rgbtGreen;

                avarageGreen /= 9.0;

                avarageBlue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                              image[i - 1][j + 1].rgbtBlue;

                avarageBlue +=
                    image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;

                avarageBlue += image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                               image[i + 1][j + 1].rgbtBlue;

                avarageBlue /= 9.0;
            }

            blurred_image[i][j].rgbtRed = round(avarageRed);
            blurred_image[i][j].rgbtGreen = round(avarageGreen);
            blurred_image[i][j].rgbtBlue = round(avarageBlue);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurred_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurred_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurred_image[i][j].rgbtBlue;
        }
    }
}
