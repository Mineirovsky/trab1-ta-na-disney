#ifndef KNN_BATCH_H
#define KNN_BATCH_H

#include "knn.h"
#include "result.h"
#include "config_file.h"

#if __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Testa uma série de pontos conta uma coleção de treino e armazena o
 * resultado em um vetor de resultados
 *
 * @param n Tamanho do espaço dimensional dos pontos
 * @param dataset Coleção de treino
 * @param dataset_s Tamanho da coleção de treino
 * @param testset Coleção de testes
 * @param testset_s Tamanho da coleção de testes
 * @param conf Objeto de configuração
 * @return Result* Vetor de resultados, do mesmo tamanho que a coleção de testes
 */
Result *knn_batch(
    unsigned int n,
    KnnDP *dataset,
    unsigned int dataset_s,
    KnnDP *testset,
    unsigned int testset_s,
    Conf conf
);

#if __cplusplus
}
#endif // __cplusplus
#endif // KNN_BATCH_H
