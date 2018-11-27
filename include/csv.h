#ifndef CSV_H
#define CSV_H

#if __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Objeto que armazena uma tabela CSV importada
 *
 */
typedef struct csv_instance
{
    char title[32]; /** Título da tabela */
    float *data; /** Vetor de posições da tabela */
    unsigned int columns; /** Número de colunas na tabela */
    unsigned int rows; /** Número de linhas na tabela */
} Csv;

/**
 * @brief Importa um arquivo CSV
 *
 * @param file_path String com o caminho para o arquivo CSV
 * @return Csv Objeto de tabela
 */
Csv csv_import (char *file_path);

/**
 * @brief Gera um ponteiro para uma posição na tabela CSV
 *
 * @param csv Objeto de tabela
 * @param row Linha a ser encontrada
 * @param col Coluna a ser encontrada
 * @return float* Ponteiro para a posição apontada
 */
float *csv_map (Csv csv, unsigned int row, unsigned int col);

/**
 * @brief Limpa a memória alocada por um objeto Csv
 *
 * @param csv
 */
void csv_delete (Csv *csv);

/**
 * @brief Imprime a tabela CSV
 *
 * @param csv Objeto de tabela
 */
void csv_print (Csv csv);


#if __cplusplus
}
#endif // __cplusplus
#endif // CSV_H
