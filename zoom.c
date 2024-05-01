/* lib_ppm.h */
#include "lib_ppm.h"
#include "stdio.h"
#include <stdlib.h>

int numberOfSquaresToBePainted(int RorGorB, int K);
int HasToBePainted(int numberOfSquares, int k);

int main(void)
{
    struct image_s data;
    struct image_s *image = &data;

    struct image_s newData;
    struct image_s *newImage = &newData;

    read_ppm("lena.ppm", image);

    int newWidth = image->width * 3;
    int newHeight = image->height * 3;

    newImage->width = newWidth;
    newImage->height = newHeight;

    newImage->pix = malloc(newWidth * newHeight * sizeof(struct pixel_s));

    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            int positionInOldImage = i * image->width + j;

            int Red = image->pix[positionInOldImage].r;
            int Green = image->pix[positionInOldImage].g;
            int Blue = image->pix[positionInOldImage].b;

            for (int k = 0; k < 3; k++)
            {
                int numberOfSquaresRed = numberOfSquaresToBePainted(Red, k);
                int numberOfSquaresGreen = numberOfSquaresToBePainted(Green, k);
                int numberOfSquaresBlue = numberOfSquaresToBePainted(Blue, k);

                int LineInNewImage = (i * 3 + k) * newWidth;

                int positionInNewImageRed = LineInNewImage + (j * 3);
                int positionInNewImageGreen = LineInNewImage + (j * 3 + 1);
                int positionInNewImageBlue = LineInNewImage + (j * 3 + 2);

                newImage->pix[positionInNewImageRed].r = HasToBePainted(numberOfSquaresRed, k) * 255;
                newImage->pix[positionInNewImageGreen].g = HasToBePainted(numberOfSquaresGreen, k) * 255;
                newImage->pix[positionInNewImageBlue].b = HasToBePainted(numberOfSquaresBlue, k) * 255;
            }
        }
    }

    write_ppm("copy.ppm", newImage);
};

int HasToBePainted(int NumberOfSquares, int K)
{
    if (NumberOfSquares == 3)
    {
        return 1;
    }

    if (NumberOfSquares == 0)
    {
        return 0;
    }

    if (NumberOfSquares == 1)
    {
        if (K == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if (NumberOfSquares == 2)
    {
        if (K == 0 || K == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    return 0;
};

int numberOfSquaresToBePainted(int RorGorB, int K)
{
    int numberOfSquaresToBePainted = 0;
    if (RorGorB >= 180)
    {
        numberOfSquaresToBePainted = 3;
    }
    else if (RorGorB >= 135)
    {
        numberOfSquaresToBePainted = 2;
    }
    else if (RorGorB >= 75)
    {
        numberOfSquaresToBePainted = 1;
    }
    else
    {
        numberOfSquaresToBePainted = 0;
    }
    return numberOfSquaresToBePainted;
};