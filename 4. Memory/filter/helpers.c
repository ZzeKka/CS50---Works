#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum, mean;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            sum = image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen;
            mean = round(sum / 3.0);
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width / 2; ++j)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    memcpy(image_copy, image, height * width * sizeof(RGBTRIPLE));
    float count;
    int sum_red, sum_blue, sum_green;
    int mean_red, mean_blue, mean_green;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            sum_red = 0, sum_blue = 0, sum_green = 0;
            mean_red = 0, mean_blue = 0, mean_green = 0;
            count = 0.0;
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                if (i + 1 < height)
                {
                    sum_red += image_copy[i + 1][j].rgbtRed;
                    sum_blue += image_copy[i + 1][j].rgbtBlue;
                    sum_green += image_copy[i + 1][j].rgbtGreen;
                    count += 1;
                }
                if (i - 1 >= 0)
                {
                    sum_red += image_copy[i - 1][j].rgbtRed;
                    sum_blue += image_copy[i - 1][j].rgbtBlue;
                    sum_green += image_copy[i - 1][j].rgbtGreen;
                    count += 1;
                }
                if (j + 1 < width)
                {
                    sum_red += image_copy[i][j + 1].rgbtRed;
                    sum_blue += image_copy[i][j + 1].rgbtBlue;
                    sum_green += image_copy[i][j + 1].rgbtGreen;
                    count += 1;
                }
                if (j - 1 >= 0)
                {
                    sum_red += image_copy[i][j - 1].rgbtRed;
                    sum_blue += image_copy[i][j - 1].rgbtBlue;
                    sum_green += image_copy[i][j - 1].rgbtGreen;
                    count += 1;
                }
                if (i + 1 < width && j + 1 < height)
                {
                    sum_red += image_copy[i + 1][j + 1].rgbtRed;
                    sum_blue += image_copy[i + 1][j + 1].rgbtBlue;
                    sum_green += image_copy[i + 1][j + 1].rgbtGreen;
                    count += 1;
                }
                if (i + 1 < width && j - 1 >= 0)
                {
                    sum_red += image_copy[i + 1][j - 1].rgbtRed;
                    sum_blue += image_copy[i + 1][j - 1].rgbtBlue;
                    sum_green += image_copy[i + 1][j - 1].rgbtGreen;
                    count += 1;
                }
                if (i - 1 >= 0 && j + 1 < height)
                {
                    sum_red += image_copy[i - 1][j + 1].rgbtRed;
                    sum_blue += image_copy[i - 1][j + 1].rgbtBlue;
                    sum_green += image_copy[i - 1][j + 1].rgbtGreen;
                    count += 1;
                }
                if (i - 1 >= 0 && j - 1 >= 0)
                {
                    sum_red += image_copy[i - 1][j - 1].rgbtRed;
                    sum_blue += image_copy[i - 1][j - 1].rgbtBlue;
                    sum_green += image_copy[i - 1][j - 1].rgbtGreen;
                    count += 1;
                }
                sum_red += image_copy[i][j].rgbtRed;
                sum_blue += image_copy[i][j].rgbtBlue;
                sum_green += image_copy[i][j].rgbtGreen;
                count += 1;
            }
            else
            {
                sum_red += image_copy[i + 1][j].rgbtRed;
                sum_blue += image_copy[i + 1][j].rgbtBlue;
                sum_green += image_copy[i + 1][j].rgbtGreen;
                sum_red += image_copy[i - 1][j].rgbtRed;
                sum_blue += image_copy[i - 1][j].rgbtBlue;
                sum_green += image_copy[i - 1][j].rgbtGreen;
                sum_red += image_copy[i][j + 1].rgbtRed;
                sum_blue += image_copy[i][j + 1].rgbtBlue;
                sum_green += image_copy[i][j + 1].rgbtGreen;
                sum_red += image_copy[i][j - 1].rgbtRed;
                sum_blue += image_copy[i][j - 1].rgbtBlue;
                sum_green += image_copy[i][j - 1].rgbtGreen;
                sum_red += image_copy[i + 1][j + 1].rgbtRed;
                sum_blue += image_copy[i + 1][j + 1].rgbtBlue;
                sum_green += image_copy[i + 1][j + 1].rgbtGreen;
                sum_red += image_copy[i + 1][j - 1].rgbtRed;
                sum_blue += image_copy[i + 1][j - 1].rgbtBlue;
                sum_green += image_copy[i + 1][j - 1].rgbtGreen;
                sum_red += image_copy[i - 1][j + 1].rgbtRed;
                sum_blue += image_copy[i - 1][j + 1].rgbtBlue;
                sum_green += image_copy[i - 1][j + 1].rgbtGreen;
                sum_red += image_copy[i - 1][j - 1].rgbtRed;
                sum_blue += image_copy[i - 1][j - 1].rgbtBlue;
                sum_green += image_copy[i - 1][j - 1].rgbtGreen;
                sum_red += image_copy[i][j].rgbtRed;
                sum_blue += image_copy[i][j].rgbtBlue;
                sum_green += image_copy[i][j].rgbtGreen;
                count += 9;
            }
            mean_red = round(sum_red / count);
            mean_blue = round(sum_blue / count);
            mean_green = round(sum_green / count);
            image[i][j].rgbtRed = mean_red;
            image[i][j].rgbtBlue = mean_blue;
            image[i][j].rgbtGreen = mean_green;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE image_copy[height][width];
    memcpy(image_copy, image, height * width * sizeof(RGBTRIPLE));
    float sum_red_gx, sum_blue_gx, sum_green_gx;
    float sum_red_gy, sum_blue_gy, sum_green_gy;
    int sobel_red, sobel_blue, sobel_green;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            sum_red_gx = 0.0, sum_blue_gx = 0.0, sum_green_gx = 0.0;
            sum_red_gy = 0.0, sum_blue_gy = 0.0, sum_green_gy = 0.0;
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                if (i + 1 < height)
                {
                    sum_red_gx += image_copy[i + 1][j].rgbtRed * gx[2][1];
                    sum_blue_gx += image_copy[i + 1][j].rgbtBlue * gx[2][1];
                    sum_green_gx += image_copy[i + 1][j].rgbtGreen * gx[2][1];
                    sum_red_gy += image_copy[i + 1][j].rgbtRed * gy[2][1];
                    sum_blue_gy += image_copy[i + 1][j].rgbtBlue * gy[2][1];
                    sum_green_gy += image_copy[i + 1][j].rgbtGreen * gy[2][1];
                }
                if (i - 1 >= 0)
                {
                    sum_red_gx += image_copy[i - 1][j].rgbtRed * gx[0][1];
                    sum_blue_gx += image_copy[i - 1][j].rgbtBlue * gx[0][1];
                    sum_green_gx += image_copy[i - 1][j].rgbtGreen * gx[0][1];
                    sum_red_gy += image_copy[i - 1][j].rgbtRed * gy[0][1];
                    sum_blue_gy += image_copy[i - 1][j].rgbtBlue * gy[0][1];
                    sum_green_gy += image_copy[i - 1][j].rgbtGreen * gy[0][1];
                }
                if (j + 1 < width)
                {
                    sum_red_gx += image_copy[i][j + 1].rgbtRed * gx[1][2];
                    sum_blue_gx += image_copy[i][j + 1].rgbtBlue * gx[1][2];
                    sum_green_gx += image_copy[i][j + 1].rgbtGreen * gx[1][2];
                    sum_red_gy += image_copy[i][j + 1].rgbtRed * gy[1][2];
                    sum_blue_gy += image_copy[i][j + 1].rgbtBlue * gy[1][2];
                    sum_green_gy += image_copy[i][j + 1].rgbtGreen * gy[1][2];
                }
                if (j - 1 >= 0)
                {
                    sum_red_gx += image_copy[i][j - 1].rgbtRed * gx[1][0];
                    sum_blue_gx += image_copy[i][j - 1].rgbtBlue * gx[1][0];
                    sum_green_gx += image_copy[i][j - 1].rgbtGreen * gx[1][0];
                    sum_red_gy += image_copy[i][j - 1].rgbtRed * gy[1][0];
                    sum_blue_gy += image_copy[i][j - 1].rgbtBlue * gy[1][0];
                    sum_green_gy += image_copy[i][j - 1].rgbtGreen * gy[1][0];
                }
                if (i + 1 < width && j + 1 < height)
                {
                    sum_red_gx += image_copy[i + 1][j + 1].rgbtRed * gx[2][2];
                    sum_blue_gx += image_copy[i + 1][j + 1].rgbtBlue * gx[2][2];
                    sum_green_gx += image_copy[i + 1][j + 1].rgbtGreen * gx[2][2];
                    sum_red_gy += image_copy[i + 1][j + 1].rgbtRed * gy[2][2];
                    sum_blue_gy += image_copy[i + 1][j + 1].rgbtBlue * gy[2][2];
                    sum_green_gy += image_copy[i + 1][j + 1].rgbtGreen * gy[2][2];
                }
                if (i + 1 < width && j - 1 >= 0)
                {
                    sum_red_gx += image_copy[i + 1][j - 1].rgbtRed * gx[2][0];
                    sum_blue_gx += image_copy[i + 1][j - 1].rgbtBlue * gx[2][0];
                    sum_green_gx += image_copy[i + 1][j - 1].rgbtGreen * gx[2][0];
                    sum_red_gy += image_copy[i + 1][j - 1].rgbtRed * gy[2][0];
                    sum_blue_gy += image_copy[i + 1][j - 1].rgbtBlue * gy[2][0];
                    sum_green_gy += image_copy[i + 1][j - 1].rgbtGreen * gy[2][0];
                }
                if (i - 1 >= 0 && j + 1 < height)
                {
                    sum_red_gx += image_copy[i - 1][j + 1].rgbtRed * gx[0][2];
                    sum_blue_gx += image_copy[i - 1][j + 1].rgbtBlue * gx[0][2];
                    sum_green_gx += image_copy[i - 1][j + 1].rgbtGreen * gx[0][2];
                    sum_red_gy += image_copy[i - 1][j + 1].rgbtRed * gy[0][2];
                    sum_blue_gy += image_copy[i - 1][j + 1].rgbtBlue * gy[0][2];
                    sum_green_gy += image_copy[i - 1][j + 1].rgbtGreen * gy[0][2];
                }
                if (i - 1 >= 0 && j - 1 >= 0)
                {
                    sum_red_gx += image_copy[i - 1][j - 1].rgbtRed * gx[0][0];
                    sum_blue_gx += image_copy[i - 1][j - 1].rgbtBlue * gx[0][0];
                    sum_green_gx += image_copy[i - 1][j - 1].rgbtGreen * gx[0][0];
                    sum_red_gy += image_copy[i - 1][j - 1].rgbtRed * gy[0][0];
                    sum_blue_gy += image_copy[i - 1][j - 1].rgbtBlue * gy[0][0];
                    sum_green_gy += image_copy[i - 1][j - 1].rgbtGreen * gy[0][0];
                }
                sum_red_gx += image_copy[i][j].rgbtRed * gx[1][1];
                sum_blue_gx += image_copy[i][j].rgbtBlue * gx[1][1];
                sum_green_gx += image_copy[i][j].rgbtGreen * gx[1][1];
                sum_red_gy += image_copy[i][j].rgbtRed * gy[1][1];
                sum_blue_gy += image_copy[i][j].rgbtBlue * gy[1][1];
                sum_green_gy += image_copy[i][j].rgbtGreen * gy[1][1];
            }
            else
            {
                sum_red_gx += image_copy[i + 1][j].rgbtRed * gx[2][1];
                sum_blue_gx += image_copy[i + 1][j].rgbtBlue * gx[2][1];
                sum_green_gx += image_copy[i + 1][j].rgbtGreen * gx[2][1];
                sum_red_gy += image_copy[i + 1][j].rgbtRed * gy[2][1];
                sum_blue_gy += image_copy[i + 1][j].rgbtBlue * gy[2][1];
                sum_green_gy += image_copy[i + 1][j].rgbtGreen * gy[2][1];
                sum_red_gx += image_copy[i - 1][j].rgbtRed * gx[0][1];
                sum_blue_gx += image_copy[i - 1][j].rgbtBlue * gx[0][1];
                sum_green_gx += image_copy[i - 1][j].rgbtGreen * gx[0][1];
                sum_red_gy += image_copy[i - 1][j].rgbtRed * gy[0][1];
                sum_blue_gy += image_copy[i - 1][j].rgbtBlue * gy[0][1];
                sum_green_gy += image_copy[i - 1][j].rgbtGreen * gy[0][1];
                sum_red_gx += image_copy[i][j + 1].rgbtRed * gx[1][2];
                sum_blue_gx += image_copy[i][j + 1].rgbtBlue * gx[1][2];
                sum_green_gx += image_copy[i][j + 1].rgbtGreen * gx[1][2];
                sum_red_gy += image_copy[i][j + 1].rgbtRed * gy[1][2];
                sum_blue_gy += image_copy[i][j + 1].rgbtBlue * gy[1][2];
                sum_green_gy += image_copy[i][j + 1].rgbtGreen * gy[1][2];
                sum_red_gx += image_copy[i][j - 1].rgbtRed * gx[1][0];
                sum_blue_gx += image_copy[i][j - 1].rgbtBlue * gx[1][0];
                sum_green_gx += image_copy[i][j - 1].rgbtGreen * gx[1][0];
                sum_red_gy += image_copy[i][j - 1].rgbtRed * gy[1][0];
                sum_blue_gy += image_copy[i][j - 1].rgbtBlue * gy[1][0];
                sum_green_gy += image_copy[i][j - 1].rgbtGreen * gy[1][0];
                sum_red_gx += image_copy[i + 1][j + 1].rgbtRed * gx[2][2];
                sum_blue_gx += image_copy[i + 1][j + 1].rgbtBlue * gx[2][2];
                sum_green_gx += image_copy[i + 1][j + 1].rgbtGreen * gx[2][2];
                sum_red_gy += image_copy[i + 1][j + 1].rgbtRed * gy[2][2];
                sum_blue_gy += image_copy[i + 1][j + 1].rgbtBlue * gy[2][2];
                sum_green_gy += image_copy[i + 1][j + 1].rgbtGreen * gy[2][2];
                sum_red_gx += image_copy[i + 1][j - 1].rgbtRed * gx[2][0];
                sum_blue_gx += image_copy[i + 1][j - 1].rgbtBlue * gx[2][0];
                sum_green_gx += image_copy[i + 1][j - 1].rgbtGreen * gx[2][0];
                sum_red_gy += image_copy[i + 1][j - 1].rgbtRed * gy[2][0];
                sum_blue_gy += image_copy[i + 1][j - 1].rgbtBlue * gy[2][0];
                sum_green_gy += image_copy[i + 1][j - 1].rgbtGreen * gy[2][0];
                sum_red_gx += image_copy[i - 1][j + 1].rgbtRed * gx[0][2];
                sum_blue_gx += image_copy[i - 1][j + 1].rgbtBlue * gx[0][2];
                sum_green_gx += image_copy[i - 1][j + 1].rgbtGreen * gx[0][2];
                sum_red_gy += image_copy[i - 1][j + 1].rgbtRed * gy[0][2];
                sum_blue_gy += image_copy[i - 1][j + 1].rgbtBlue * gy[0][2];
                sum_green_gy += image_copy[i - 1][j + 1].rgbtGreen * gy[0][2];
                sum_red_gx += image_copy[i - 1][j - 1].rgbtRed * gx[0][0];
                sum_blue_gx += image_copy[i - 1][j - 1].rgbtBlue * gx[0][0];
                sum_green_gx += image_copy[i - 1][j - 1].rgbtGreen * gx[0][0];
                sum_red_gy += image_copy[i - 1][j - 1].rgbtRed * gy[0][0];
                sum_blue_gy += image_copy[i - 1][j - 1].rgbtBlue * gy[0][0];
                sum_green_gy += image_copy[i - 1][j - 1].rgbtGreen * gy[0][0];
                sum_red_gx += image_copy[i][j].rgbtRed * gx[1][1];
                sum_blue_gx += image_copy[i][j].rgbtBlue * gx[1][1];
                sum_green_gx += image_copy[i][j].rgbtGreen * gx[1][1];
                sum_red_gy += image_copy[i][j].rgbtRed * gy[1][1];
                sum_blue_gy += image_copy[i][j].rgbtBlue * gy[1][1];
                sum_green_gy += image_copy[i][j].rgbtGreen * gy[1][1];
            }
            sobel_red = round(sqrt((sum_red_gx * sum_red_gx) + (sum_red_gy * sum_red_gy)));
            sobel_blue = round(sqrt((sum_blue_gx * sum_blue_gx) + (sum_blue_gy * sum_blue_gy)));
            sobel_green = round(sqrt((sum_green_gx * sum_green_gx) + (sum_green_gy * sum_green_gy)));
            if (sobel_red > 255)
            {
                sobel_red = 255;
            }
            if (sobel_blue > 255)
            {
                sobel_blue = 255;
            }
            if (sobel_green > 255)
            {
                sobel_green = 255;
            }
            image[i][j].rgbtRed = sobel_red;
            image[i][j].rgbtBlue = sobel_blue;
            image[i][j].rgbtGreen = sobel_green;
        }
    }
    return;
}
