#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int id = strlen(input) - 1;
    char last_char;

    // Base Case
    if (id == 0)
    {
        last_char = input[0];
        return last_char - 48;
    }
    // Recursion
    else
    {
        last_char = input[id];
        input[id] = '\0';
        return (last_char - 48) + 10 * convert(input);
    }

}