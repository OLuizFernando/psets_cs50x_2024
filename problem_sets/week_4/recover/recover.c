#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    uint8_t buffer[512];

    int jpegs_count = 0;

    char filename[8];

    FILE *image = NULL;

    while (fread(buffer, sizeof(uint8_t), 512, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 &&
            buffer[3] <= 0xef)
        {
            if (jpegs_count != 0)
            {
                fclose(image);
            }

            sprintf(filename, "%03i.jpg", jpegs_count);

            image = fopen(filename, "w");

            fwrite(buffer, sizeof(uint8_t), 512, image);

            jpegs_count++;
        }
        else if (jpegs_count != 0)
        {
            fwrite(buffer, sizeof(uint8_t), 512, image);
        }
    }

    fclose(image);
    fclose(card);
}
