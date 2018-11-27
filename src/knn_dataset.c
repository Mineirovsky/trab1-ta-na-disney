/**
 * @file knn_dataset.c
 * @author Gabriel Mineiro (gabrielpfgmineiro@gmail.com)
 * @brief Módulo para importar e lidar coleções de pontos
 * @version 1.0
 * @date 2018-11-27
 *
 * @copyright Copyright (c) 2018
 *
 */
#include "csv.h"
#include "knn.h"
#include <stdlib.h>
#include <string.h>

KnnDP *knn_dataset_from_csv (Csv csv)
{
    // Aloca espaço para o dataset
    KnnDP *dataset = malloc(sizeof(KnnDP) * csv.rows);
    // Ponteiro para a linha atual da tabela
    float *row_ptr;

    // O tamanho do espaço vetorial do dataset é uma unidade menor que a quantidade
    // de colunas na tabela csv
    unsigned int n = csv.columns - 1;


    for (int i = 0; i < csv.rows; i++)
    {
        // Seta o ponteiro para a linha da tabela correta
        row_ptr = csv_map(csv, i, 0);
        // Inicializa o ponto e aloca espaço para os valores
        dataset[i] = knn_new(row_ptr[n], malloc(sizeof(float) * n));

        // Copia os valores do ponto
        memcpy(dataset[i].data, row_ptr, sizeof(float) * n);
    }

    return dataset;
}

void knn_dataset_delete (KnnDP *dataset, unsigned int dataset_s)
{
    for (int i = 0; i < dataset_s; i++)
    {
        knn_delete(dataset + i);
    }

    free(dataset);
    dataset = NULL;
}

void knn_dataset_print (KnnDP *dataset, unsigned int dataset_s, unsigned int n)
{
    for (int i = 0; i < dataset_s; i++)
    {
        knn_print(dataset + i, n);
    }
}
