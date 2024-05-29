#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int centavos;
    do
    {
        centavos = get_int("Change owed: ");
    }
    while (centavos < 0);

    int moedas = 0;

    while (centavos / 25 > 0)
    {
        moedas += 1;
        centavos -= 25;
    }

    while (centavos / 10 > 0)
    {
        moedas += 1;
        centavos -= 10;
    }

    while (centavos / 5 > 0)
    {
        moedas += 1;
        centavos -= 5;
    }

    while (centavos / 1 > 0)
    {
        moedas += 1;
        centavos -= 1;
    }

    printf("%i\n", moedas);
}
