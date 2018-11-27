/**
 * @file result.c
 * @author Gabriel Mineiro (gabrielpfgmineiro@gmail.com)
 * @brief Módulo para lidar com resultados de baterias de testes
 * @version 1.0
 * @date 2018-11-27
 *
 * @copyright Copyright (c) 2018
 *
 */
#include "result.h"
#include "confusion_matrix.h"
#include "knn.h"
#include <stdio.h>
#include <stdlib.h>

void result_fprint(Result result, FILE *result_file)
{
    // Imprime métricas
    fprintf(result_file, "%.2f\n\n", result.accuracy);
    cm_fprint(&result.cm, result_file);
    printf("\n");

    // Imprime cada label encontrada
    for (int i = 0; i < result.samples; i++)
    {
        fprintf(result_file, "%.0f\n", result.predictions[i]);
    }
}

void result_print(Result result)
{
    result_fprint(result, stdout);
}

void result_delete(Result *result)
{
    if (result->predictions)
    {
        free(result->predictions);
        result->predictions = NULL;
    }

    cm_delete(&result->cm);
}
