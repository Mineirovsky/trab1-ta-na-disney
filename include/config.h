#include <stdio.h>

typedef struct conf_run_setup
{
    unsigned int k;
    char algorithm;
    float r;
} ConfRS;

typedef struct conf_conf
{
    char *training_file;
    char *testing_file;
    char *results_dir;
    unsigned int runs;
    ConfRS *run_setups;
} Conf;

Conf get_config (FILE *conf_file);

void print_rs (ConfRS rs);

void print_config (Conf conf);

void conf_delete (Conf *conf);