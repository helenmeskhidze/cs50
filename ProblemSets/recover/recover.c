#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check input
    if (argc != 2)
    {
        printf("Usage ./recover FILE\n");
        return 1;
    }

    // open input file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // length of the blocks of jpeg files for temp storage
    int jpeg = 512;
    uint8_t buffer[jpeg];

    // reserve for the string formatter
    char filename[8];
    int jpegCount = 0;
    sprintf(filename, "%03i.jpg", jpegCount);
    FILE *img = fopen(filename, "w");

    while (fread(buffer, 1, jpeg, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // the very first jpeg header
            if (jpegCount == 0)
            {
                fwrite(buffer, 1, jpeg, img);
                jpegCount++;
            }
            // all other new jpeg headers (close existing file and open new)
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpegCount);
                img = fopen(filename, "w");
                fwrite(buffer, 1, jpeg, img);
                jpegCount++;
            }
        }
        // write everything between headers to the open file
        else
        {
            if (jpegCount > 0)
            {
                fwrite(buffer, 1, jpeg, img);
            }
        }
    }
    fclose(img);
    fclose(card);
}
