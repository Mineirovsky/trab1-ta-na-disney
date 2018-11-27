/**
 * @file distancia.c
 * @author Gabriel Mineiro (gabrielpfgmineiro@gmail.com)
 * @brief Módulo para calcular distâncias
 * @version 1.0
 * @date 2018-11-27
 *
 * @copyright Copyright (c) 2018
 *
 */
#include "distancia.h"
#include <stdlib.h>
#include <math.h>

/**
 * @brief Função privada para encontrar o maior valor da lista
 *
 * @param n Tamanho da lista
 * @param list Lista
 * @return float* Ponteiro para o maior valor
 */
float *_distancia_maxf (unsigned int n, float *list)
{
    // Ponteiro para armazenar o maior já encontrado
    float *bigger = list;

    // Itera por cada valor da lista
    for (int i = 1; i < n; i++)
    {
        // Procura por valores maiores dos que o já encontrado
        if (list[i] > *bigger)
        {
            // Grava o ponteiro do novo maior valor
            bigger = list + i;
        }
    }

    return bigger;
}

float distancia_euclidiana (unsigned int n, float *p, float *q)
{
    // Acumulador para o somatório
    float acc = 0.0;

    // Soma as distâncias calculadas em cada eixo
    for (int i = 0; i < n; i++)
    {
        acc += powf(p[i] - q[i], 2.0);
    }

    // Retorna a raiz quadrada do somatório
    return sqrtf(acc);
}

float distancia_chebyshev (unsigned int n, float *p, float *q)
{
    // Vetor para armazenar as distâncias em cada eixo
    float *dist_axis = malloc(sizeof(float) * n);
    float distancia;

    // Calcula e registra as distâncias de cada eixo
    for (int i = 0; i < n; i++)
    {
        dist_axis[i] = fabsf(*(p + i) - *(q + i));
    }

    // Encontra a maior distância dos eixos
    distancia = *(_distancia_maxf(n, dist_axis));

    // Libera o vetor dos eixos
    free(dist_axis);

    return distancia;
}

float distancia_minkowski (unsigned int n, float *p, float *q, float r)
{
    // Acumulador para o somatório
    float acc = 0.0;

    // Soma as distâncias calculadas em cada eixo
    for (int i = 0; i < n; i++)
    {
        acc += powf(fabsf(p[i] - q[i]), r);
    }

    // Retorna a potência normalizada do somatório
    return powf(acc, 1.0 / r);
}
