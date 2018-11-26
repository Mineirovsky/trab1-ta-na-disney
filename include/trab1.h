#ifndef TRAB1_H
#define TRAB1_H

#include "trab1.h"
#include "config_file.h"
#include "csv.h"
#include "knn.h"
#include "knn_dataset.h"
#include "knn_batch.h"
#include "result.h"
#include "confusion_matrix.h"
#include <stdio.h>
#include <string.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

int g_verbose = 0; /** Variável global para exibir detalhes sobre a execução */

int main(int argc, char const *argv[]);

void print_help ();

#if __cplusplus
}
#endif // __cplusplus
#endif // TRAB1_H
