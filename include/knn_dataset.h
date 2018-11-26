#ifndef CSV_KNN_H
#define CSV_KNN_H

#include "csv.h"
#include "knn.h"

#if __cplusplus
extern "C" {
#endif // __cplusplus

KnnDP *knn_dataset_from_csv (Csv csv);

void knn_dataset_delete (KnnDP *dataset, unsigned int dataset_s);

void knn_dataset_print (KnnDP *dataset, unsigned int dataset_s, unsigned int n);

#if __cplusplus
}
#endif // __cplusplus
#endif // CSV_KNN_H