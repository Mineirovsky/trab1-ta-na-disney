/**
 * @file knn_dataset.h
 * @author Gabriel Mineiro (gabrielpfgmineiro@gmail.com)
 * @brief Módulo para importar e lidar coleções de pontos
 * @version 1.0
 * @date 2018-11-27
 *
 * @copyright Copyright (c) 2018
 *
 */
#ifndef CSV_KNN_H
#define CSV_KNN_H

#include "csv.h"
#include "knn.h"

#if __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Gera um dataset de KnnDP a partir de um objeto de tabela CSV
 *
 * @param csv Objeto de tabela
 * @return KnnDP* Vetor de pontos
 */
KnnDP *knn_dataset_from_csv (Csv csv);

/**
 * @brief Limpa a memória alocada por um dataset
 *
 * @param dataset Dataset
 * @param dataset_s Tamanho do dataset
 */
void knn_dataset_delete (KnnDP *dataset, unsigned int dataset_s);

/**
 * @brief Imprime o conteúdo de um dataset
 *
 * @param dataset Dataset a ser impresso
 * @param dataset_s Tamanho do dataset
 * @param n Tamanho do espaço vetorial do dataset
 */
void knn_dataset_print (KnnDP *dataset, unsigned int dataset_s, unsigned int n);

#if __cplusplus
}
#endif // __cplusplus
#endif // CSV_KNN_H