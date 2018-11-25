#ifndef TRAB1_H
#define TRAB1_H

#include <stdio.h>
#include <distancia.h>

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
