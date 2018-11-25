#ifndef DISTANCIA_H
#define DISTANCIA_H

#include <stdlib.h>
#include <math.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Calcula a distância euclidiana dos pontos p e q num espaço n-dimensional
 *
 * @param n Dimensões espaciais
 * @param p Vetor de coordenadas p
 * @param q Vetor de coordenadas q
 * @return float Distância euclidiana
 */
float distancia_euclidiana (unsigned int n, float *p, float *q);

/**
 * @brief Calcula a distância de Chebyshev para os pontos p e q num espaço n-dimensional
 *
 * @param n Dimensões espaciais
 * @param p Vetor de coordenadas p
 * @param q Vetor de coordenadas q
 * @return float Distância de Chebyshev
 */
float distancia_chebyshev (unsigned int n, float *p, float *q);

/**
 * @brief Calcula a distância de Minkowski para os pontos p e q num espaço n-dimensional
 *
 * @param n Dimensões espaciais
 * @param p Vetor de coordenadas p
 * @param q Vetor de coordenadas q
 * @param r Expoente r
 * @return float Distância de Minkowski
 */
float distancia_minkowski (unsigned int n, float *p, float *q, float r);

#if __cplusplus
}
#endif // __cplusplus
#endif // DISTANCIA_H
