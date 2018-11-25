#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int _csv_count_columns(FILE  *file)
{
    unsigned int counter = 1;
    char c;

    do
    {
        c = getc(file);
        if (c == ',') counter++;
    } while (!(c == '\n' || c == EOF));

    return counter;
}

unsigned int _csv_count_rows(FILE *file)
{
    unsigned int counter = 0;
    char c;

    do
    {
        c = getc(file);
        if (c == '\n') counter++;
    } while (c != EOF);

    return counter;
}

int _csv_next_col(FILE *file)
{
    char c;

    do
    {
        c = getc(file);
        if (c == ',') break;
        if (c == '\n' || c == EOF) return 0;
    } while (c != EOF);

    return 1;
}

int _csv_next_row(FILE *file)
{
    char c;

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
    FILE *file;
    unsigned int columns, rows;

    file = fopen(file_path, "r");
    if (!file) {
        printf("[CSV] ERROR: File could not be opened\n");
        csv.data = NULL;
        csv.columns = 0;
        csv.rows = 0;
        return csv;
    }

    columns = _csv_count_columns(file);

    rewind(file);

    rows = _csv_count_rows(file);

    rewind(file);

    strcpy(csv.title, "Dataset");
    csv.columns = columns;
    csv.rows = rows;

    csv.data = malloc(sizeof(float) * columns * rows);

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
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

    fclose(file);

    return csv;
}


float *csv_map (Csv csv, unsigned int row, unsigned int col)
{
    return csv.data + csv.columns * row + col;
}

void csv_delete (Csv *csv)
{
    free(csv->data);
    csv->data = NULL;
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

    for (int col = 0; col < csv.columns; col++)
    {
        printf("|%d|\t", col);
    }
    printf("\n");
    for (int row = 0; row < csv.rows; row++)
    {
        printf("=%d=\t", row);
        for (int col = 0; col < csv.columns; col++)
        {
            printf("%.2f\t", *csv_map(csv, row, col));
        }
        printf("\n");
    }
}