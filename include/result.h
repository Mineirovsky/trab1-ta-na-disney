#ifndef CONF_H
#define CONF_H

#include "confusion_matrix.h"
#include "knn.h"

#if __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Objeto para armazenar o resultado de uma bateria de testes
 *
 */
typedef struct result_result
{
    ConfusionMatrix cm; /** Matriz de confusão */
    float accuracy; /** Acurácia */
    unsigned int assertions; /** Quantidade de acertos */
    KnnLabel *predictions; /** Vetor de predições */
    unsigned int samples; /** Quantidade de amostras testadas */
} Result;

/**
 * @brief Imprime resultado para uma stream ou arquivo
 *
 * @param result Objeto de resultado
 * @param result_file Arquivo ou stream a ser impresso
 */
void result_fprint(Result result, FILE *result_file);

/**
 * @brief Imprime resultado
 *
 * @param result Objeto de resultado
 */
void result_print(Result result);

/**
 * @brief Limpa a memória alocada por um resultado
 *
 * @param result Objeto de resultado
 */
void result_delete(Result *result);

#if __cplusplus
}
#endif // __cplusplus
#endif // CONF_H
