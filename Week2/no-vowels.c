// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.c>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string str);

int main(int argc, string argv[])
{
    // If no argument
    if (argc < 2)
    {
        printf("Please input a word!\n");
        return 1;
    }
    // If more than one argument
    else if (argc > 2)
    {
        printf("This program supports only one word as argument!\n");
        return 1;
    }
    else
    {
        string replaced_str = replace(argv[1]);
        printf("%s\n", replaced_str);
    }

}

string replace(string str)
{
    char vowel_map[5] = {'6', '3', '1', '0', 'u'};
    char curr_char;
    for (int i = 0, len = strlen(str); i < len; i++)
    {
        curr_char = tolower(str[i]);
        switch (curr_char)
        {
            case 'a':
                if (vowel_map[0] != 'a')
                {
                    curr_char = vowel_map[0];
                    str[i] = curr_char;
                    break;
                }

            case 'e':
                if (vowel_map[1] != 'e')
                {
                    curr_char = vowel_map[1];
                    str[i] = curr_char;
                    break;
                }

            case 'i':
                if (vowel_map[2] != 'i')
                {
                    curr_char = vowel_map[2];
                    str[i] = curr_char;
                    break;
                }


            case 'o':
                if (vowel_map[3] != 'o')
                {
                    curr_char = vowel_map[3];
                    str[i] = curr_char;
                    break;
                }


            case 'u':
                if (vowel_map[4] != 'u')
                {
                    curr_char = vowel_map[4];
                    str[i] = curr_char;
                    break;
                }
        }
    }

    return str;
}
