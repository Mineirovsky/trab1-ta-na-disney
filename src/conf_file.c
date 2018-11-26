#include "config_file.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Mede o tamanho da linha a partir da posição atual no arquivo
 *
 * @param conf_file Arquivo
 * @return unsigned int Tamanho da linha
 */
unsigned int _conf_line_length (FILE *conf_file)
{
    char c;
    unsigned int count = 1;

    do
    {
        c = fgetc(conf_file);
        if (c == '\n' || c == EOF) break;
        else count++;

    } while (c != EOF);

    fseek(conf_file, -(long int)count, SEEK_CUR);

    return count;
}

/**
 * @brief Aloca espaço, copia a linha a partir da posição atual do arquivo e
 * move o cursor para a próxima linha
 *
 * @param conf_file Arquivo
 * @return char* String com a linha
 */
char *_conf_get_line (FILE *conf_file)
{
    long int fpos = ftell(conf_file);
    unsigned int length = _conf_line_length(conf_file);

    char *string = malloc(sizeof(char) * length);

    fgets(string, length, conf_file);
    fseek(conf_file, fpos + (long)length, SEEK_SET);

    return string;
}

/**
 * @brief Conta quantos parâmetros existem em uma string, divididos por vírgulas
 *
 * @param string String a ser verificada
 * @return int Número de parâmetros
 */
int _conf_param_count(char *string)
{
    unsigned int counter = 1;
    int i = 0;
    do
    {
        if (string[i] == ',')
        {
            if (!(string[i + 1] == ','  || string[i + 1] == '\0')) counter++;
            else
            {
                return -1;
            }
        }
        i++;
    } while ((string[i]) != '\0');

    return counter;
}

/**
 * @brief Carrega os parâmetros de teste na posição atual do arquivo e avança
 * para a próxima linha
 *
 * @param conf_file Arquivo
 * @return ConfRS Objeto com parâmetros de teste
 */
ConfRS _conf_get_rs (FILE *conf_file)
{
    ConfRS rs;
    char *string = _conf_get_line(conf_file);
    int param_count = _conf_param_count(string);


    switch (param_count)
    {
        case 2:
            sscanf(string, "%d, %c", &rs.k, &rs.algorithm);
            rs.r = 0.0;
            break;

        case 3:
            sscanf(string, "%d, %c, %f", &rs.k, &rs.algorithm, &rs.r);
            break;
        case -1:
            puts("Invalid param sintax");
            free(string);
            exit(EXIT_FAILURE);
        default:
            puts("Invalid param");
            free(string);
            exit(EXIT_FAILURE);
            break;
    }

    free(string);

    // Garantir que o caracter do algorítmo é maiúsculo
    if (rs.algorithm >= 'a' && rs.algorithm <= 'z')
        rs.algorithm -= 'a' - 'A';

    return rs;
}

/**
 * @brief Conta quantas linhas não vazias ainda existem da posição atual até o
 * final do arquivo
 *
 * @param conf_file Arquivo
 * @return unsigned int Linhas remanescentes
 */
unsigned int _conf_count_remaining_lines (FILE *conf_file)
{
    int counter = 1;
    char c;
    long int fpos = ftell(conf_file);

    do
    {
        c = fgetc(conf_file);
        if (c == '\n')
        {
            c = fgetc(conf_file);
            if (c != EOF) counter++;
            fseek(conf_file, -1, SEEK_CUR);
        }
    } while (c != EOF);

    fseek(conf_file, fpos, SEEK_SET);

    return counter;
}

Conf get_config (FILE *conf_file)
{
    Conf conf;
    conf.training_file = _conf_get_line(conf_file);
    conf.testing_file = _conf_get_line(conf_file);
    conf.results_dir = _conf_get_line(conf_file);

    conf.runs = _conf_count_remaining_lines(conf_file);

    conf.run_setups = malloc(sizeof(ConfRS) * conf.runs);

    for (int i = 0; i < conf.runs; i++)
    {
        conf.run_setups[i] = _conf_get_rs(conf_file);
    }

    return conf;
}

void conf_delete (Conf *conf)
{
    if (!conf->training_file)
    free(conf->training_file);
    conf->training_file = NULL;

    if (!conf->testing_file)
    free(conf->testing_file);
    conf->testing_file = NULL;

    if (!conf->results_dir)
    free(conf->results_dir);
    conf->results_dir = NULL;

    if (!conf->run_setups)
    free(conf->run_setups);
    conf->run_setups = NULL;
}
void print_rs (ConfRS rs)
{
    printf("k: %d, a: %c, r: %.2f\n", rs.k, rs.algorithm, rs.r);
}

void print_config (Conf conf)
{
    printf("Training file: %s\n", conf.training_file);
    printf("Testing file: %s\n", conf.testing_file);
    printf("Results dir: %s\n", conf.results_dir);

    for (int i = 0; i < conf.runs; i++)
    {
        print_rs(conf.run_setups[i]);
    }
}
