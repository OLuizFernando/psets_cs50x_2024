#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calc_letras(string texto);
int calc_palavras(string texto);
int calc_sentencas(string texto);

int main(void)
{
    string texto = get_string("Text: ");

    int letras = calc_letras(texto);
    int palavras = calc_palavras(texto);
    int sentencas = calc_sentencas(texto);

    float l = letras / ((float) palavras / 100);
    float s = sentencas / ((float) palavras / 100);

    float clindex = 0.0588 * l - 0.296 * s - 15.8;
    int clindex_int = (int) round(clindex);

    if (clindex_int < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (clindex_int >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", clindex_int);
    }
}

int calc_letras(string texto)
{
    int soma = 0;
    int tamanho = strlen(texto);

    for (int i = 0; i < tamanho; i++)
    {
        if (isalpha(texto[i]))
        {
            soma++;
        }
    }

    return soma;
}

int calc_palavras(string texto)
{
    int soma = 0;
    int tamanho = strlen(texto);

    for (int i = 0; i < tamanho; i++)
    {
        if (texto[i] == ' ')
        {
            soma++;
        }
    }

    return soma + 1;
}

int calc_sentencas(string texto)
{
    int soma = 0;
    int tamanho = strlen(texto);

    for (int i = 0; i < tamanho; i++)
    {
        if (texto[i] == '!' || texto[i] == '.' || texto[i] == '?')
        {
            soma++;
        }
    }

    return soma;
}
