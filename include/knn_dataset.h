#ifndef CSV_KNN_H
#define CSV_KNN_H

#include "csv.h"
#include "knn.h"

#if __cplusplus
extern "C" {
#endif // __cplusplus

knn_dp *knn_dataset_from_csv (Csv csv);

void knn_dataset_delete (knn_dp *dataset, unsigned int dataset_s);

void knn_dataset_print (knn_dp *dataset, unsigned int dataset_s, unsigned int n);

#if __cplusplus
}
#endif // __cplusplus
#endif // CSV_KNN_H