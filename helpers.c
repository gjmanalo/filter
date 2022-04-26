#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.00000000);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double tempRed = 0;
    double tempGreen = 0;
    double tempBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempRed = round((0.189*image[i][j].rgbtBlue + 0.769*image[i][j].rgbtGreen + 0.393*image[i][j].rgbtRed));

            tempGreen = round((0.168*image[i][j].rgbtBlue + 0.686*image[i][j].rgbtGreen + 0.349*image[i][j].rgbtRed));

            tempBlue = round((0.131*image[i][j].rgbtBlue + 0.534*image[i][j].rgbtGreen + 0.272*image[i][j].rgbtRed));

            if (tempRed < 255)
            {
                image[i][j].rgbtRed = tempRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if (tempGreen < 255)
            {
                image[i][j].rgbtGreen = tempGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (tempBlue < 255)
            {
                image[i][j].rgbtBlue = tempBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
         }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j < (width/2) + 1; j++)
        {
            RGBTRIPLE temp = image[i][j - 1];
            image[i][j - 1] = image[i][width - j];
            image[i][width - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

//MIDDLE PIXELS
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            double sumblue = 0;
            double sumgreen = 0;
            double sumred = 0;
            for (int n = -1; n <= 1; n++)
            {
                for (int m = -1; m <= 1; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/9);
            sumgreen = round(sumgreen/9);
            sumred = round(sumred/9);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;
        }
    }
//TOP EDGE
        int i = 0;
        for (int j = 1; j < width; j++)
        {
            double sumblue = 0;
            double sumgreen = 0;
            double sumred = 0;
            for (int n = 0; n <= 1; n++)
            {
                for (int m = -1; m <= 1; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/6);
            sumgreen = round(sumgreen/6);
            sumred = round(sumred/6);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;
        }

//BOTTOM EDGE
        i = height - 1;
        for (int j = 1; j < width; j++)
        {
            double sumblue = 0;
            double sumgreen = 0;
            double sumred = 0;
            for (int n = -1; n <= 0; n++)
            {
                for (int m = -1; m <= 1; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/6);
            sumgreen = round(sumgreen/6);
            sumred = round(sumred/6);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;
        }

//LEFT EDGE
    int j = 0;
    for (i = 1; i < height; i++)
    {
            double sumblue = 0;
            double sumgreen = 0;
            double sumred = 0;
            for (int n = -1; n <= 1; n++)
            {
                for (int m = 0; m <= 1; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/6);
            sumgreen = round(sumgreen/6);
            sumred = round(sumred/6);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;
    }

//RIGHT EDGE
    j = width - 1;
    for (i = 1; i < height; i++)
    {
            double sumblue = 0;
            double sumgreen = 0;
            double sumred = 0;
            for (int n = -1; n <= 1; n++)
            {
                for (int m = -1; m <= 0; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/6);
            sumgreen = round(sumgreen/6);
            sumred = round(sumred/6);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;
    }

//TOP LEFT CORNER
            i = 0;
            j = 0;
            double sumblue = 0;
            double sumgreen = 0;
            double sumred = 0;
            for (int n = 0; n <= 1; n++)
            {
            for (int m = 0; m <= 1; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/4);
            sumgreen = round(sumgreen/4);
            sumred = round(sumred/4);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;

//TOP RIGHT CORNER
            i = 0;
            j = width - 1;
            sumblue = 0;
            sumgreen = 0;
            sumred = 0;
            for (int n = 0; n <= 1; n++)
            {
                for (int m = -1; m <= 0; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/4);
            sumgreen = round(sumgreen/4);
            sumred = round(sumred/4);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;

//BOTTOM LEFT CORNER
            i = height - 1;
            j = 0;
            sumblue = 0;
            sumgreen = 0;
            sumred = 0;
            for (int n = -1; n <= 0; n++)
            {
                for (int m = 0; m <= 1; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/4);
            sumgreen = round(sumgreen/4);
            sumred = round(sumred/4);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;

//BOTTOM RIGHT CORNER
            i = height - 1;
            j = width - 1;
            sumblue = 0;
            sumgreen = 0;
            sumred = 0;
            for (int n = -1; n <= 0; n++)
            {
                for (int m = -1; m <= 0; m++)
                {
                     sumblue = sumblue + copy[i + n][j + m].rgbtBlue;
                     sumgreen = sumgreen + copy[i + n][j + m].rgbtGreen;
                     sumred = sumred + copy[i + n][j + m].rgbtRed;
                }
            }
            sumblue = round(sumblue/4);
            sumgreen = round(sumgreen/4);
            sumred = round(sumred/4);
            image[i][j].rgbtBlue = sumblue;
            image[i][j].rgbtGreen = sumgreen;
            image[i][j].rgbtRed = sumred;

    return;
}
