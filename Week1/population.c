#include <cs50.c>
#include <stdio.h> 

int main(void)
{
    // TODO: Prompt for start size
    int n_0 = 0;
    while (n_0 < 9)
    {
        n_0 = get_int("Intial population size: ");
    }

    // TODO: Prompt for end size
    int n_f = 0;
    while (n_f < n_0)
    {
        n_f = get_int("Final population size: ");
    }
    // TODO: Calculate number of years until we reach threshold
    int n = n_0;
    int birth_rate = n / 3;
    int death_rate = n / 4;
    int years;

    for (years = 0; n < n_f; years++)
    {
        n = n + birth_rate - death_rate;
        birth_rate = n / 3;
        death_rate = n / 4;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}
