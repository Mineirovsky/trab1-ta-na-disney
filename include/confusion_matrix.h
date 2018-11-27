#ifndef CONF_MATRIX_H
#define CONF_MATRIX_H

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Estrutura para acomodar uma matriz de confusão
 *
 */
typedef struct confusion_matrix
{
    unsigned int size; /** Largura da matriz */
    unsigned int *data; /** Vetor de valores da matriz */
    int *labels; /** Lista de labels */
} ConfusionMatrix;

/**
 * @brief Inicializa uma nova instância da matriz
 *
 * @param size Largura da matriz
 * @return ConfusionMatrix Nova instância da matriz
 */
ConfusionMatrix cm_new (unsigned int size);

/**
 * @brief Defina as labels da matriz
 *
 * @param cm Matriz de confusão
 * @param labels Lista de labels, do mesmo tamanho da largura da matriz
 */
void cm_set_labels (ConfusionMatrix *cm, int *labels);

/**
 * @brief Gera um ponteiro para a posição da matriz
 *
 * @param cm Matriz de confusão
 * @param predicted Linha
 * @param correct Coluna
 * @return unsigned int* Ponteiro para a posição na matriz
 */
unsigned int *cm_map (ConfusionMatrix *cm, unsigned int predicted, unsigned int correct);

/**
 * @brief Encontra a posição de uma label na lista de uma matriz de confusão
 *
 * @param cm Matriz de confusão
 * @param label Label a ser encontrada
 * @return unsigned _cm_label_pos Posição da label
 */
unsigned int _cm_label_pos (ConfusionMatrix *cm, int label);

/**
 * @brief Incrementa o contador na posição da matriz
 *
 * @param cm Matriz de confusão
 * @param predicted Label classificada
 * @param correct Label correta
 * @return int Se a label classificada é igual a correta
 */
int cm_inc (ConfusionMatrix *cm, unsigned int predicted, unsigned int correct);

/**
 * @brief Limpa a memória alocada por uma matriz de confusão
 *
 * @param cm
 */
void cm_delete (ConfusionMatrix *cm);

/**
 * @brief Imprime para um stream a matriz
 *
 * @param cm Matriz de confusão
 * @param dest Stream de destino
 * @return int Número de caracteres impressos
 */
int cm_fprint (ConfusionMatrix *cm, FILE *dest);

/**
 * @brief Imprime a matriz
 *
 * @param cm Matriz de confusão
 * @return int Número de caracteres impressos
 */
int cm_print (ConfusionMatrix *cm);

#if __cplusplus
}
#endif // __cplusplus
#endif // CONF_MATRIX_H
