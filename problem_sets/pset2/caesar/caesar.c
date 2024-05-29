#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encriptar(string texto, int chave);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./caesar chave\n");
        return 1;
    }

    for (int i = 0, tamanho = strlen(argv[1]); i < tamanho; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar chave\n");
            return 1;
        }
    }

    int chave = atoi(argv[1]);
    string texto = get_string("plaintext: ");

    encriptar(texto, chave);
}

void encriptar(string texto, int chave)
{
    int tamanho = strlen(texto);
    char texto_encriptado[tamanho];
    int shift;

    for (int i = 0; i < tamanho; i++)
    {
        if (isalpha(texto[i]))
        {
            if (isupper(texto[i]))
            {
                shift = 65;
            }
            else
            {
                shift = 97;
            }

            texto_encriptado[i] = texto[i] - shift;
            texto_encriptado[i] += chave;
            texto_encriptado[i] %= 26;
            texto_encriptado[i] += shift;
        }
        else
        {
            texto_encriptado[i] = texto[i];
        }
    }

    texto_encriptado[tamanho] = '\0';

    printf("ciphertext: %s\n", texto_encriptado);
}
