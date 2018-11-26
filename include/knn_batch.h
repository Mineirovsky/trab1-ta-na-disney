#ifndef KNN_BATCH_H
#define KNN_BATCH_H

#include "knn.h"
#include "result.h"
#include "config_file.h"

#if __cplusplus
extern "C" {
#endif // __cplusplus

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
