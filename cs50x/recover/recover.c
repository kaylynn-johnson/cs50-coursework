#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
const int FILENAME_SIZE = 8;

int main(int argc, char *argv[])
{
    // ensure correct number of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover <filename>\n");
        return 1;
    }

    // try to open file from user
    FILE *recovery_image = fopen(argv[1], "r");
    if (recovery_image == NULL)
    {
        printf("Couldn't open file, %s\n", argv[1]);
        return 1;
    }

    // define variables
    uint8_t buffer[BLOCK_SIZE];
    int i = 0;
    char filename[FILENAME_SIZE];

    // create first file
    sprintf(filename, "%03d.jpg", i);
    FILE *image = fopen(filename, "w");
    if (image == NULL)
    {
        printf("Couldn't create file, %s\n", filename);
        return 1;
    }

    // find the first header of first image to get the ball rolling
    while (fread(buffer, BLOCK_SIZE, 1, recovery_image) != 0)
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xF0) == 0xe0))
        {
            fwrite(buffer, BLOCK_SIZE, 1, image);
            break;
        }
    }

    // continue reading in continuous images from recovery_image and output to file
    while (fread(buffer, BLOCK_SIZE, 1, recovery_image) != 0)
    {
        // check first bytes to see if this is the start of new image
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xF0) == 0xe0))
        {
            // close previous image
            fclose(image);

            // open new image
            i++;
            sprintf(filename, "%03d.jpg", i);
            image = fopen(filename, "w");
            if (image == NULL)
            {
                printf("Couldn't create file, %s\n", filename);
                return 1;
            }
        }

        // write to the image
        fwrite(buffer, BLOCK_SIZE, 1, image);
    }

    fclose(recovery_image);
    fclose(image);

    return 0;
}
