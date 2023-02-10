#include <cs50.c>
#include <stdio.h>

int main(void)
{
    //Gets height of pyramid
    int h = 0;
    while (h < 1 || h > 8)
    {
        h = get_int("Height: ");
    }

    char space = ' ';
    char block = '#';
    int row_length = h + 2; // Partial row_length (only accounts for the left pyramid and middle spacing)

    // First for-loop for each row
    for (int row = 1; row <= h; row++)
    {
        row_length ++; // Full row_length
        // Second for-loop prints a row
        for (int i = 1; i <= row_length; i++)
        {
            //Condition for printing spaces
            if (i <= h - row || (i > h && i <= h + 2))
            {
                printf("%c", space);
            }
            else //Printing blocks
            {
                printf("%c", block);
            }
        }
        printf("\n");
    }

}

