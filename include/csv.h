#ifndef CSV_H
#define CSV_H

#if __cplusplus
extern "C" {
#endif // __cplusplus
typedef struct csv_instance
{
    char title[32];
    float *data;
    unsigned int columns;
    unsigned int rows;
} Csv;

Csv csv_import (char *file_path);

float *csv_map (Csv csv, unsigned int row, unsigned int col);

void csv_delete (Csv *csv);

void csv_print (Csv csv);


#if __cplusplus
}
#endif // __cplusplus
#endif // CSV_H
