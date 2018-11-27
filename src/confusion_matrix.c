#include "confusion_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ConfusionMatrix cm_new (unsigned int size)
{
    ConfusionMatrix cm;
    cm.size = size;
    cm.data = malloc(sizeof(int) * size * size);
    cm.labels = malloc(sizeof(int) * size);

    // Zera todos os espaços da matriz
    for (int i = 0; i < (size * size); i++)
    {
        cm.data[i] = 0;
    }

    return cm;
}

void cm_set_labels (ConfusionMatrix *cm, int *labels) {
    memcpy(cm->labels, labels, sizeof(int) * cm->size);
}

unsigned int *cm_map (ConfusionMatrix *cm, unsigned int predicted, unsigned int correct)
{
    return cm->data + cm->size * predicted + correct;
}

unsigned int _cm_label_pos (ConfusionMatrix *cm, int label)
{
    // Procura pela lebel na lista de labels da matriz de confusão
    for (int i = 0; i < cm->size; i++)
    {
        if (cm->labels[i] == label) return i;
    }

    // Retorna o tamanho da matriz caso a label não seja encontrada
    return cm->size;
}

int cm_inc (ConfusionMatrix *cm, unsigned int predicted, unsigned int correct)
{
    // Encontra a posição das labels na lista de labels
    unsigned int predicted_pos = _cm_label_pos(cm, predicted);
    unsigned int correct_pos = _cm_label_pos(cm, correct);

    // Verifica se a label está listada
    if (predicted_pos == cm->size || correct_pos == cm->size)
    {
        printf("[ConfusionMatrix] ERROR: A given label is not listed");
    } else
    {
        // Incrementa a posição adequada da matriz
        (*cm_map(cm, predicted_pos, correct_pos))++;
    }

    return predicted == correct;
}

void cm_delete (ConfusionMatrix *cm)
{
    if (cm->data)
    {
        free(cm->data);
        cm->data = NULL;
    }

    if (cm->labels)
    {
        free(cm->labels);
        cm->labels = NULL;
    }
}

int cm_fprint (ConfusionMatrix *cm, FILE *dest)
{
    int char_count = 0;
    for (int i = 0; i < cm->size; i++)
    {
        for (int j = 0; j < cm->size; j++)
        {
            char_count += fprintf(dest, "%d", *cm_map(cm, i, j));
            if (fputc((j < (cm->size - 1) ? ' ' : '\n'), dest) != EOF) char_count++;
        }
    }

    return char_count;
}

int cm_print (ConfusionMatrix *cm)
{
    return cm_fprint(cm, stdout);
}
