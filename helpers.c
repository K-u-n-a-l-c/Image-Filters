#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
                int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtGreen);
                int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtGreen);
                int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtGreen);
                
                if(sepiaRed > 255)
                sepiaRed = 255;
                
                if(sepiaGreen > 255)
                sepiaGreen = 255;
                
                if(sepiaBlue > 255)
                sepiaBlue = 255;
                
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
    for(int i = 0; i < height; i++)
    {
        int t = width;
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image [i][j];
            image[i][j] = image [i][t-1];
            image [i][t-1] = temp;
            t--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumRed = 0;
            int sumGreen = 0;
            float counter = 0.00;
            
            for(int k = -1; k < 2; k++)
            {
                for(int h = -1; h < 2; h++)
                {
                    if(i + k < 0 || i + k > height - 1 || j + h < 0 || j + h > width - 1)
                    {
                        continue;
                    }
                    sumBlue += image[i+k][j+h].rgbtBlue;
                    sumGreen += image[i+k][j+h].rgbtGreen;
                    sumRed += image[i+k][j+h].rgbtRed;
                    
                    counter++;
                }
            }
            temp[i][j].rgbtBlue = round(sumBlue/counter);
            temp[i][j].rgbtRed = round(sumRed/counter);
            temp[i][j].rgbtGreen = round(sumGreen/counter);
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
