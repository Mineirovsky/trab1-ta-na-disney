#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Função privada que conta quantas colunas tem na tabela
 *
 * @param file Arquivo CSV
 * @return unsigned int Quantidade de colunas
 */
unsigned int _csv_count_columns(FILE  *file)
{
    unsigned int counter = 1;
    char c;

    // Conta cada vírgula em uma linha
    do
    {
        c = getc(file);
        if (c == ',') counter++;
    } while (!(c == '\n' || c == EOF));

    return counter;
}

/**
 * @brief Função privada que conta quantas linhas tem na tabela
 *
 * @param file Arquivo CSV
 * @return unsigned int Quantidade de linhas
 */
unsigned int _csv_count_rows(FILE *file)
{
    unsigned int counter = 0;
    char c;

    // Conta quantas quebras de linha há no arquivo
    do
    {
        c = getc(file);
        if (c == '\n') counter++;
    } while (c != EOF);

    return counter;
}

/**
 * @brief Função privada para avançar o ponteiro de um arquivo para o início da
 * próxima coluna
 *
 * @param file Arquivo CSV
 * @return int Indicador se a linha ou o arquivo não acabou antes
 */
int _csv_next_col(FILE *file)
{
    char c;

    // Procura pela próxima vírgula
    do
    {
        c = getc(file);
        if (c == ',') break;
        if (c == '\n' || c == EOF) return 0;
    } while (c != EOF);

    return 1;
}

/**
 * @brief Função privada para avançar para a próxima linha
 *
 * @param file Arquivo CSV
 * @return int Indicador se o arquivo não acabou antes
 */
int _csv_next_row(FILE *file)
{
    char c;

    // Procura pela próxima quebra de linha
    do
    {
        c = getc(file);
        if (c == '\n') break;
        if (c == EOF) return 0;
    } while (c != EOF);

    return 1;
}

Csv csv_import (char *file_path)
{
    Csv csv;
    unsigned int columns, rows;

    // Abre o arquivo CSV
    FILE *file = fopen(file_path, "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (!file) {
        printf("[CSV] ERROR: File could not be opened\n");
        csv.data = NULL;
        csv.columns = 0;
        csv.rows = 0;
        return csv;
    }

    // Conta quantas colunas tem no arquivo CSV
    columns = _csv_count_columns(file);

    // Retorna o ponteiro do arquivo para o início para poder medir a quantidade de linhas
    rewind(file);

    // Conta quantas linhas tem no arquivo CSV
    rows = _csv_count_rows(file);

    // Retorna o ponteiro para iniciar a cópia
    rewind(file);

    // Inicializa um título para o arquivo CSV
    strcpy(csv.title, "Dataset");

    // Copia a quantidade de linhas e colunas para o objeto de tabela
    csv.columns = columns;
    csv.rows = rows;

    // Aloca espaço para a tabela
    csv.data = malloc(sizeof(float) * columns * rows);

    // Itera por cada linha da tabela
    for (int row = 0; row < rows; row++)
    {
        // Itera por cada coluna
        for (int col = 0; col < columns; col++)
        {
            // Copia o valor da posição e verifica se o formato corresponde ao esperado
            if (!fscanf(file, "%f", csv_map(csv, row, col)))
            {
                printf("[CSV] ERROR: invalid data at row #%d, column #%d\n", row, col);

                fclose(file);
                csv_delete(&csv);

                return csv;
            }

            if (col == columns - 1)
                _csv_next_row(file);
            else
            {
                // Verifica se a linha não é menor do que devia
                if (!_csv_next_col(file))
                {
                    printf("[CSV] ERROR: row #%d is shorter than expected\n", row);

                    fclose(file);
                    csv_delete(&csv);

                    return csv;
                }
            }
        }
    }

    // Fecha o arquivo CSV
    fclose(file);

    return csv;
}


float *csv_map (Csv csv, unsigned int row, unsigned int col)
{
    return csv.data + csv.columns * row + col;
}

void csv_delete (Csv *csv)
{
    if (csv->data)
    {
        free(csv->data);
        csv->data = NULL;
    }
}

void csv_print (Csv csv)
{
    printf("Table title: %s\n", csv.title);
    if (!csv.data)
    {
        printf("[Empty table]\n");
        return;
    }
    printf("\t");

    // Imprime guias de colunas
    for (int col = 0; col < csv.columns; col++)
    {
        printf("|%d|\t", col);
    }
    printf("\n");
    for (int row = 0; row < csv.rows; row++)
    {
        printf("=%d=\t", row); // Imprime guias de linhas
        for (int col = 0; col < csv.columns; col++)
        {
            printf("%.2f\t", *csv_map(csv, row, col));
        }
        printf("\n");
    }
}