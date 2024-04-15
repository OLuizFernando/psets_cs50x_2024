#include <cs50.h>
#include <stdio.h>

bool algoritmo_luhns(long num);
int multiplicar_e_quebrar(int num);
int verificar_tamanho(long num);
int verificar_primeiros_digitos(long num, int tamanho);

int main(void)
{
    long num = get_long("Number: ");

    int valido = algoritmo_luhns(num);
    int tamanho = verificar_tamanho(num);
    int primeiros_digitos = verificar_primeiros_digitos(num, tamanho);

    if (valido)
    {
        if (tamanho == 15 && (primeiros_digitos == 34 || primeiros_digitos == 37))
        {
            printf("AMEX\n");
        }
        else if (tamanho == 16 && primeiros_digitos >= 51 && primeiros_digitos <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if ((tamanho == 13 || tamanho == 16) && primeiros_digitos >= 40 &&
                 primeiros_digitos <= 49)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

bool algoritmo_luhns(long num)
{
    int soma1 = 0;
    int soma2 = 0;
    bool intercalado = false;

    while (num > 0)
    {
        if (intercalado)
        {
            soma1 += multiplicar_e_quebrar(num % 10);
        }
        else
        {
            soma2 += num % 10;
        }

        num /= 10;
        intercalado = !intercalado;
    }

    int soma_final = soma1 + soma2;

    if (soma_final % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int multiplicar_e_quebrar(int num)
{
    num *= 2;

    if (num > 9)
    {
        int soma = 0;

        soma += num % 10;
        num /= 10;
        soma += num;

        return soma;
    }
    else
    {
        return num;
    }
}

int verificar_tamanho(long num)
{
    int digitos = 0;

    for (int i = 0; num > 0; i++)
    {
        num /= 10;
        digitos++;
    }

    return digitos;
}

int verificar_primeiros_digitos(long num, int tamanho)
{
    long divisor = 1;

    for (int i = 2; i < tamanho; i++)
    {
        divisor *= 10;
    }

    int primeiros_digitos = num / divisor;

    return primeiros_digitos;
}
