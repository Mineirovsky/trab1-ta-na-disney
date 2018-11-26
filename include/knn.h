#ifndef KNN_H
#define KNN_H

#include <stdlib.h>
#include <math.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

typedef float KnnLabel;

/**
 * @brief Uma estrutura para acomodar um ponto de dado
 *
 */
typedef struct knn_datapoint
{
    KnnLabel label; /** Classe do ponto */
    float *data; /** Vetor de coordenadas do ponto */
} KnnDP;

/**
 * @brief Cria uma nova instância de um ponto de dados
 *
 * @param label Classe do ponto
 * @param data Vetor de coordenadas
 * @return KnnDP Nova instancia de ponto de dados
 */
KnnDP knn_new (KnnLabel label, float *data);

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
    KnnDP *p,
    KnnDP *q,
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
    KnnDP *q; /** Referência ao ponto */
    float distance; /** Distância calculada */
} KnnDT;

KnnDT knn_dt_new(KnnDP *p, float distance);

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
    KnnDP *p,
    KnnDP *dataset,
    unsigned int dataset_s,
    unsigned int n,
    KnnDT *distances,
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
 * @return KnnLabel
 */
KnnLabel knn_classify (
    KnnDP *p,
    KnnDP *dataset,
    unsigned int dataset_s,
    unsigned int n,
    unsigned int k,
    KnnDA da,
    float r
);

void knn_delete (KnnDP *dp);

void knn_print (KnnDP *dp, unsigned int n);

typedef struct knn_label_list
{
    unsigned int count;
    KnnLabel *labels;
} KnnLL;

KnnLL knn_get_labels (KnnDP *dataset, unsigned int dataset_s);

#if __cplusplus
}
#endif // __cplusplus
#endif // KNN_H
