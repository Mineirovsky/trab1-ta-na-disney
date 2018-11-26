#include "csv.h"
#include "knn.h"
#include <stdlib.h>
#include <string.h>

KnnDP *knn_dataset_from_csv (Csv csv)
{
    KnnDP *dataset = malloc(sizeof(KnnDP) * csv.rows);
    float *row_ptr;
    unsigned int n = csv.columns - 1;

    for (int i = 0; i < csv.rows; i++)
    {
        row_ptr = csv_map(csv, i, 0);
        dataset[i] = knn_new(row_ptr[n], malloc(sizeof(float) * n));

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
