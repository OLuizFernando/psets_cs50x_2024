#include <cs50.h>
#include <stdio.h>
#include <string.h>

int calcular_pontos(string palavra);

int pontos[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int pontos_p1 = calcular_pontos(p1);
    int pontos_p2 = calcular_pontos(p2);

    if (pontos_p1 > pontos_p2)
    {
        printf("Player 1 Wins!\n");
    }
    else if (pontos_p2 > pontos_p1)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int calcular_pontos(string palavra)
{
    int soma = 0;
    int letra;

    for (int i = 0, tamanho = strlen(palavra); i < tamanho; i++)
    {
        if (palavra[i] >= 65 && palavra[i] <= 90)
        {
            soma += pontos[palavra[i] - 65];
        }
        else if (palavra[i] >= 97 && palavra[i] <= 122)
        {
            soma += pontos[palavra[i] - 97];
        }
    }

    return soma;
}
