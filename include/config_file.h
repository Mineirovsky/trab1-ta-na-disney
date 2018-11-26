#ifndef CONF_FILE_H
#define CONF_FILE_H

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Parâmetros para KNN
 *
 */
typedef struct conf_run_setup
{
    unsigned int k; /** Valor k */
    char algorithm; /** Algorítmo de distância a ser usado */
    float r; /** Minkowski p-norm */
} ConfRS;

/**
 * @brief Configurações para a execução
 *
 */
typedef struct conf_conf
{
    char *training_file; /** Caminho para o arquivo CSV de treino */
    char *testing_file; /** Caminho para o arquivo CSV de testes */
    char *results_dir;  /** Caminho para o diretório de resultados */
    unsigned int runs; /** Número de testes */
    ConfRS *run_setups; /** Parâmetros para os testes */
} Conf;

/**
 * @brief Carrega as configurações em um objeto
 *
 * @param conf_file Arquivo de configuração
 * @return Conf Objeto de configurações
 */
Conf get_config (FILE *conf_file);

/**
 * @brief Imprime um parâmetro de teste
 *
 * @param rs Objeto de parâmetros
 */
void print_rs (ConfRS rs);

/**
 * @brief Imprime um objeto de configurações
 *
 * @param conf Objeto de configurações
 */
void print_config (Conf conf);

/**
 * @brief Limpa a memória alocada por um objeto de configurações
 *
 * @param conf Objeto de configurações
 */
void conf_delete (Conf *conf);

#if __cplusplus
}
#endif // __cplusplus
#endif // CONF_H
