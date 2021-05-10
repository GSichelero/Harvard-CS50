#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            int mean = round((red + blue + green)/3.0);

            image[i][j].rgbtRed = mean;
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtGreen = mean;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfWidth;
    int reversePixel;
    int red, green, blue;

    if (width % 2 != 0)
    {
        halfWidth = (width + 1) / 2;
    }
    else
    {
        halfWidth = width / 2;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfWidth; j++)
        {
            red = image[i][j].rgbtRed;
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;

            reversePixel = width - j - 1;

            image[i][j].rgbtRed = image[i][reversePixel].rgbtRed;
            image[i][j].rgbtBlue = image[i][reversePixel].rgbtBlue;
            image[i][j].rgbtGreen = image[i][reversePixel].rgbtGreen;

            image[i][reversePixel].rgbtRed = red;
            image[i][reversePixel].rgbtBlue = blue;
            image[i][reversePixel].rgbtGreen = green;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    int redMean;
    int blueMean;
    int greenMean;

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            redMean = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 9.0);
            blueMean = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 9.0);
            greenMean = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 9.0);

            image2[i][j].rgbtRed = redMean;
            image2[i][j].rgbtBlue = blueMean;
            image2[i][j].rgbtGreen = greenMean;
        }
    }

    for (int i = 1; i < height - 1; i++)
    {
        int j = 0;
        image2[i][0].rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
        image2[i][0].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
        image2[i][0].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);

        j = width - 1;
        image2[i][width - 1].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i][j].rgbtRed) / 6.0);
        image2[i][width - 1].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
        image2[i][width - 1].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen+ image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
    }

    for (int j = 1; j < width - 1; j++)
    {
        int i = 0;
        image2[0][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
        image2[0][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
        image2[0][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);

        i = height - 1;
        image2[height - 1][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
        image2[height - 1][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
        image2[height - 1][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
    }

    int i = 0;
    int j = 0;
    image2[0][0].rgbtRed = round((image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
    image2[0][0].rgbtBlue = round((image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
    image2[0][0].rgbtGreen = round((image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);

    i = 0;
    j = width - 1;
    image2[0][width - 1].rgbtRed = round((image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
    image2[0][width - 1].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
    image2[0][width - 1].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);

    i = height - 1;
    j = 0;
    image2[height - 1][0].rgbtRed = round((image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
    image2[height - 1][0].rgbtBlue = round((image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
    image2[height - 1][0].rgbtGreen = round((image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);

    i = height - 1;
    j = width - 1;
    image2[height - 1][width - 1].rgbtRed = round((image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
    image2[height - 1][width - 1].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
    image2[height - 1][width - 1].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    RGBTRIPLE image3[height + 2][width + 2];

    int redgx;
    int bluegx;
    int greengx;

    int redgy;
    int bluegy;
    int greengy;

    for (int i = 0; i < height + 2; i++)
    {
        image3[i][0].rgbtRed = 0;
        image3[i][0].rgbtBlue = 0;
        image3[i][0].rgbtGreen = 0;

        image3[i][width + 1].rgbtRed = 0;
        image3[i][width + 1].rgbtBlue = 0;
        image3[i][width + 1].rgbtGreen = 0;
    }

    for (int j = 0; j < width + 2; j++)
    {
        image3[0][j].rgbtRed = 0;
        image3[0][j].rgbtBlue = 0;
        image3[0][j].rgbtGreen = 0;

        image3[height + 1][j].rgbtRed = 0;
        image3[height + 1][j].rgbtBlue = 0;
        image3[height + 1][j].rgbtGreen = 0;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image3[i + 1][j + 1].rgbtRed = image[i][j].rgbtRed;
            image3[i + 1][j + 1].rgbtBlue = image[i][j].rgbtBlue;
            image3[i + 1][j + 1].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            redgx = (- image3[i - 1][j - 1].rgbtRed) + image3[i - 1][j + 1].rgbtRed + (- 2 * image3[i][j - 1].rgbtRed) + (2 * image3[i][j + 1].rgbtRed) + (- image3[i + 1][j - 1].rgbtRed) + image3[i + 1][j + 1].rgbtRed;
            bluegx = (- image3[i - 1][j - 1].rgbtBlue) + image3[i - 1][j + 1].rgbtBlue + (- 2 * image3[i][j - 1].rgbtBlue) + (2 * image3[i][j + 1].rgbtBlue) + (- image3[i + 1][j - 1].rgbtBlue) + image3[i + 1][j + 1].rgbtBlue;
            greengx = (- image3[i - 1][j - 1].rgbtGreen) + image3[i - 1][j + 1].rgbtGreen + (- 2 * image3[i][j - 1].rgbtGreen) + (2 * image3[i][j + 1].rgbtGreen) + (- image3[i + 1][j - 1].rgbtGreen) + image3[i + 1][j + 1].rgbtGreen;

            redgy = (- image3[i - 1][j - 1].rgbtRed) + (- 2 * image3[i - 1][j].rgbtRed) + (- image3[i - 1][j + 1].rgbtRed) + image3[i + 1][j - 1].rgbtRed + (2 * image3[i + 1][j].rgbtRed) + image3[i + 1][j + 1].rgbtRed;
            bluegy = (- image3[i - 1][j - 1].rgbtBlue) + (- 2 * image3[i - 1][j].rgbtBlue) + (- image3[i - 1][j + 1].rgbtBlue) + image3[i + 1][j - 1].rgbtBlue + (2 * image3[i + 1][j].rgbtBlue) + image3[i + 1][j + 1].rgbtBlue;
            greengy = (- image3[i - 1][j - 1].rgbtGreen) + (- 2 * image3[i - 1][j].rgbtGreen) + (- image3[i - 1][j + 1].rgbtGreen) + image3[i + 1][j - 1].rgbtGreen + (2 * image3[i + 1][j].rgbtGreen) + image3[i + 1][j + 1].rgbtGreen;

            if (round(sqrt(pow(redgx, 2) + pow(redgy, 2))) > 255)
            {
                image2[i - 1][j - 1].rgbtRed = 255;
            }
            else
            {
                image2[i - 1][j - 1].rgbtRed = round(sqrt(pow(redgx, 2) + pow(redgy, 2)));
            }

            if (round(sqrt(pow(bluegx, 2) + pow(bluegy, 2))) > 255)
            {
                image2[i - 1][j - 1].rgbtBlue = 255;
            }
            else
            {
                image2[i - 1][j - 1].rgbtBlue = round(sqrt(pow(bluegx, 2) + pow(bluegy, 2)));
            }

            if (round(sqrt(pow(greengx, 2) + pow(greengy, 2))) > 255)
            {
                image2[i - 1][j - 1].rgbtGreen = 255;
            }
            else
            {
                image2[i - 1][j - 1].rgbtGreen = round(sqrt(pow(greengx, 2) + pow(greengy, 2)));
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
        }
    }

    return;
}
