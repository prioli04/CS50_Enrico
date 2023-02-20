#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int block_size = 512;
typedef uint8_t BYTE;

char *left_padding(int n, int digits);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // opens the input raw file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    // Creates the buffer to store the data from fread
    BYTE *buffer = malloc(sizeof(BYTE) * block_size);
    int file_count = 0;
    FILE *outptr = NULL;
    // Loop reading through the data
    while (fread(buffer, block_size, 1, inptr) == 1)
    {
        // Checking for the jpg signature
        if (*buffer == 0xff && *(buffer + 1) == 0xd8 && *(buffer + 2) == 0xff && (*(buffer + 3) >= 0xe0 && *(buffer + 3) <= 0xef))
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            char *filename = left_padding(file_count, 3);
            filename = realloc(filename, strlen(filename) + 5);
            outptr = fopen(strcat(filename, ".jpg"), "w");
            fwrite(buffer, block_size, 1, outptr);
            free(filename);
            file_count++;

        }
        else
        {
            if (outptr != NULL)
            {
                fwrite(buffer, block_size, 1, outptr);
            }
        }
    }
    // Freeing the allocated memory and closing the files
    free(buffer);
    fclose(inptr);
    fclose(outptr);
}
// Function for adding the zeros to the left of the .jpg file name
char *left_padding(int n, int digits)
{
    // Get number of digits of n
    int len_n = snprintf(NULL, 0, "%i", n);
    // Ensuring there is room for all digits in the string
    if (len_n > digits)
    {
        digits = len_n;
    }
    // Allocating memory and converting int to string
    char *str = malloc(sizeof(char) * (len_n + 1));
    char *str_zero = calloc((digits + 1), sizeof(char));
    sprintf(str, "%i", n);
    // Special case when there are no zeros to the left
    if (digits - len_n == 0)
    {
        free(str_zero);
        return str;
    }
    else
    {
        for (int i = 0; i < digits - len_n; i++)
        {
            *(str_zero + i) = '0';
        }
        char *str_final = strcat(str_zero, str);
        free(str);
        return str_final;
    }
}
