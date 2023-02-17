// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int btoi(uint8_t *byte, int n);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    int ret = fread(header, 1, HEADER_SIZE, input);

    if (ret != HEADER_SIZE)
    {
        printf("Reading header from file failed!");
        fclose(input);
        fclose(output);
        return 1;
    }

    ret = fwrite(header, 1, HEADER_SIZE, output);

    if (ret != HEADER_SIZE)
    {
        printf("Writing header to file failed!");
        fclose(input);
        fclose(output);
        return 2;
    }

    // TODO: Read samples from input file and write updated data to output file
    int file_size = btoi(&header[40], 4);
    int sample_size = btoi(&header[34], 2);
    int n_sample = file_size / (sample_size / 8);
    int16_t buffer;

    for (int i = 0; i < n_sample; i++)
    {
        ret = fread(&buffer, 2, 1, input);
        buffer *= factor;
        ret = fwrite(&buffer, 2, 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}

int btoi(uint8_t *byte, int n)
{
    int integer = 0;

    for (int i = 0; i < n; i++)
    {
        integer += (*(byte + i) << (8 * i));
    }

    return integer;
}
