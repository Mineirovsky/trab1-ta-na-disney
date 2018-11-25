#ifndef CONF_MATRIX_H
#define CONF_MATRIX_H

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct confusion_matrix
{
    unsigned int size;
    unsigned int *data;
    int *labels;
} ConfusionMatrix;

ConfusionMatrix cm_new (unsigned int size);

void cm_set_labels (ConfusionMatrix *cm, int *labels);

unsigned int *cm_map (ConfusionMatrix *cm, unsigned int predicted, unsigned int correct);

unsigned int _cm_label_pos (ConfusionMatrix *cm, int label);

int cm_inc (ConfusionMatrix *cm, unsigned int predicted, unsigned int correct);

void cm_delete (ConfusionMatrix *cm);

int cm_fprint (ConfusionMatrix *cm, FILE *dest);

int cm_print (ConfusionMatrix *cm);

#if __cplusplus
}
#endif // __cplusplus
#endif // CONF_MATRIX_H
