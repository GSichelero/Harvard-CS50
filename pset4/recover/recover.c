#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int number_of_jpg = 0;
    int first_jpg = 0;
    BYTE buffer[512];
    char filename[9];
    FILE *img = NULL;

    FILE *f = fopen(argv[1], "r");
    if (argc != 2)
    {
        printf("You should write only the name of 1 file to recover!");
        return 1;
    }
    else
    {
        if (f == NULL)
        {
            printf("File not found!");
            return 1;
        }

        while(fread(buffer, 512, 1, f) == 1)
        {
            if (first_jpg == 0)
            {
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
                {
                    sprintf(filename, "%03i.jpg", number_of_jpg);
                    img = fopen(filename, "w");

                    fwrite(buffer, 512, 1, img);

                    first_jpg = 1;
                }
            }
            else
            {
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
                {
                    fclose(img);

                    number_of_jpg++;
                    sprintf(filename, "%03i.jpg", number_of_jpg);
                    img = fopen(filename, "w");

                    fwrite(buffer, 512, 1, img);
                }
                else
                {
                    fwrite(buffer, 512, 1, img);
                }
            }
        }

        fclose(img);
        fclose(f);

        return 0;
    }
}