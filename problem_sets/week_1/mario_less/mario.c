#include <cs50.h>
#include <stdio.h>

void espacos(int quantidade);
void fazer_piramide(int altura);
void fazer_linha(int comprimento);

int main(void)
{
    int altura;

    do
    {
        altura = get_int("Height: ");
    }
    while (altura < 1);

    fazer_piramide(altura);
}

void espacos(int quantidade)
{
    for (int i = 1; i < quantidade; i++)
    {
        printf(" ");
    }
}

void fazer_linha(int comprimento)
{
    for (int i = 0; i < comprimento; i++)
    {
        printf("#");
    }
}

void fazer_piramide(int altura)
{
    for (int i = 0; i < altura; i++)
    {
        espacos(altura - i);
        fazer_linha(i + 1);
        printf("\n");
    }
}
