#ifndef KNN_H
#define KNN_H

#include <stdlib.h>
#include <math.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

typedef float knn_label;

/**
 * @brief Uma estrutura para acomodar um ponto de dado
 *
 */
typedef struct knn_datapoint
{
    knn_label label; /** Classe do ponto */
    float *data; /** Vetor de coordenadas do ponto */
} knn_dp;

/**
 * @brief Cria uma nova instância de um ponto de dados
 *
 * @param label Classe do ponto
 * @param data Vetor de coordenadas
 * @return knn_dp Nova instancia de ponto de dados
 */
knn_dp knn_new (knn_label label, float *data);

/**
 * @brief Enumarador de nomes de algorítmos para calcular distâncias
 *
 */
typedef enum KnnDistanceAlgorithm
{
    Euclidian,
    Chebyshev,
    Minkowski
} KnnDA;

/**
 * @brief Calcula a distância entre os pontos
 *
 * @param p Ponto p
 * @param q Ponto q
 * @param n Tamanho do espaço vetorial
 * @param da Algorítmo a ser usado
 * @param r Minkowski p-norm (Usado apenas se algoritmo for de Minkowski)
 * @return float Distância calculada
 */
float knn_dist (
    knn_dp *p,
    knn_dp *q,
    unsigned int n,
    KnnDA da,
    float r
);

/**
 * @brief Um tipo para armazenar a distância em conjunto com uma referência à
 * instância desse ponto
 *
 */
typedef struct knn_distance
{
    knn_dp *q; /** Referência ao ponto */
    float distance; /** Distância calculada */
} knn_dt;

knn_dt knn_dt_new(knn_dp *p, float distance);

/**
 * @brief Calcula todas as distâncias entre p e os pontos no dataset
 *
 * @param p Ponto de referência
 * @param dataset Pontos a serem aferidos
 * @param dataset_s Tamanho do dataset
 * @param n Tamanho do espaço vetorial
 * @param distances Vetor que receberá as distâncias
 * @param da Algorítmo a ser usado
 * @param r Minkowski p-norm (Usado apenas se algoritmo for de Minkowski)
 */
void knn_measure_all (
    knn_dp *p,
    knn_dp *dataset,
    unsigned int dataset_s,
    unsigned int n,
    knn_dt *distances,
    KnnDA da,
    float r
);

/**
 * @brief Classifica um ponto
 *
 * @param p Ponto a ser classificado
 * @param dataset Coleção de pontos de referência
 * @param dataset_s Tamanho da coleção
 * @param n Tamanho do espaço vetorial
 * @param da Algorítmo de distância a ser usado
 * @param r Minkowski p-norm (Usado apenas se algoritmo for de Minkowski)
 * @return knn_label
 */
knn_label knn_classify (
    knn_dp *p,
    knn_dp *dataset,
    unsigned int dataset_s,
    unsigned int n,
    unsigned int k,
    KnnDA da,
    float r
);

void knn_delete (knn_dp *dp);

void knn_print (knn_dp *dp, unsigned int n);

typedef struct knn_label_list
{
    unsigned int count;
    knn_label *labels;
} KnnLL;
KnnLL knn_get_labels (knn_dp *dataset, unsigned int dataset_s);

#if __cplusplus
}
#endif // __cplusplus
#endif // KNN_H
