#include "config.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int _conf_line_length (FILE *conf_file)
{
    char c;
    unsigned int count;

    for (count = 1; c != EOF; count++)
    {
        c = fgetc(conf_file);
        if (c == '\n' || c == EOF) break;
    }

    fseek(conf_file, -(long int)count, SEEK_CUR);

    return count;
}

char *_conf_get_line (FILE *conf_file)
{
    long int fpos = ftell(conf_file);
    unsigned int length = _conf_line_length(conf_file);

    char *string = malloc(sizeof(char) * length);

    fgets(string, length, conf_file);
    fseek(conf_file, fpos + (long)length, SEEK_SET);

    return string;
}

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

// TESTING ONLY
void main()
{
    FILE *file = fopen("config.txt", "r");


    Conf conf = get_config(file);
    fclose(file);

    printf("Training file: %s\n", conf.training_file);
    printf("Testing file: %s\n", conf.testing_file);
    printf("Results dir: %s\n", conf.results_dir);

    ConfRS *rs;

    for (int i = 0; i < conf.runs; i++)
    {
        rs = conf.run_setups + i;
        printf("k: %d, a: %c, r: %.2f\n", rs->k, rs->algorithm, rs->r);
    }

    conf_delete(&conf);
}