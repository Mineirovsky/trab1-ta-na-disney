#ifndef CONF_H
#define CONF_H

#include "confusion_matrix.h"
#include "knn.h"

#if __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct result_result
{
    ConfusionMatrix cm;
    float accuracy;
    unsigned int assertions;
    KnnLabel *predictions;
    unsigned int samples;
} Result;

void result_fprint(Result result, FILE *result_file);

void result_print(Result result);

void result_delete(Result *result);

#if __cplusplus
}
#endif // __cplusplus
#endif // CONF_H
