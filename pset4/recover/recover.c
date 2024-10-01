#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCKSIZE = 512;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover filename.raw\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCKSIZE];
    char filename[8];  // Filename buffer
    int imgCtr = 0; // Counter for no. of images
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCKSIZE, card) == 512)
    {
        // Create JPEGs from the data

        // Check if current blocksize is a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (imgCtr == 0)
            {
                // Set filename
                sprintf(filename, "%03i.jpg", imgCtr);

                // Write into file
                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCKSIZE, img);

                imgCtr++;
            }
            else
            {
                // Close img file
                fclose(img);

                // Write next img file
                sprintf(filename, "%03i.jpg", imgCtr);
                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCKSIZE, img);
                imgCtr++;
            }
        }
        else if (imgCtr > 0)
        {
            // Continue writing as this block still belongs to current img file
            fwrite(buffer, 1, BLOCKSIZE, img);
        }
    }
    fclose(img);
    fclose(card);
    return 0;
}
