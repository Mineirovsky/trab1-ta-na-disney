#include "trab1.h"
#include "csv.h"
#include "knn.h"
#include "knn_dataset.h"
#include "confusion_matrix.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // Imprime ajuda
    if (
        argc > 1 &&
        !(
            strcmp("--help", argv[1]) &&
            strcmp("-h", argv[1]) &&
            strcmp("-?", argv[1])
        )
    )
    {
        print_help();
        return EXIT_SUCCESS;
    }

    // Variáveis para armazenar nomes de arquivos; Nomes de caminhos em sistemas
    // Linux não ultrapassam 4096 caracteres, usamos 4097 para acomodar o
    // terminador de string
    char training_filepath[4097], testing_filepath[4097], results_dirpath[4097];

    // Arquivo de configuração
    FILE *cfg = fopen("config.txt", "r");

    // Parâmetros para as medições
    char distance_algorithm = 'E';
    unsigned int k = 7;
    float r = 2.0;

    // Indicador se (1) usará arquivo de configuração ou (0) não; Pode ser
    // modificado durante o processamento dos parâmetros de execução
    int use_cfg = 1;

    // Verifica por parâmetros de execução
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            // Parãmetro que imprime detalhes sobre a execução
            if (!(strcmp("--verbose", argv[i]) && strcmp("-v", argv[i])))
            {
                // Liga o indicador para impressão
                g_verbose = 1;
            }

            // Arquivo CSV para o dataset
            else if (sscanf(argv[i], "-D=%s", training_filepath))
            {
                // Desliga o indicador para uso de arquivo de configuração
                use_cfg = 0;
            }

            // Arquivos CSV com os valores a serem testados
            else if (sscanf(argv[i], "-T=%s", testing_filepath))
            {
                // Desliga o indicador para uso de arquivo de configuração
                use_cfg = 0;
            }

            // Algorítmo de distância identificado por uma letra maiúscula
            else if (sscanf(argv[i], "-A=%c, ", &distance_algorithm))
            {
                // Desliga o indicador para uso de arquivo de configuração
                use_cfg = 0;
            }

            // Valor k para classificação
            else if (sscanf(argv[i], "-K=%d, ", &k))
            {
                // Desliga o indicador para uso de arquivo de configuração
                use_cfg = 0;
            }

            // Valor r para o algorítmo de Cherbychev
            else if (sscanf(argv[i], "-R=%f, ", &r))
            {
                // Desliga o indicador para uso de arquivo de configuração
                use_cfg = 0;
            }

            // Arquivo com os resultados
            else if (sscanf(argv[i], "-O=%s, ", results_dirpath))
            {
                // Desliga o indicador para uso de arquivo de configuração
                use_cfg = 0;
            }
        }
    }

    // Importa configurações do arquivo config.txt no diretório local
    if (use_cfg)
    {

    }

    // Importa o arquivo de treino
    Csv training_csv = csv_import(training_filepath);
    // Renomeia a tabela CSV
    strcpy(training_csv.title, "TRAINING SET");
    // Verifica se é válido
    int is_csv_valid = !!training_csv.data;


    if (g_verbose)
    {
        puts(is_csv_valid ? "TRAINING CSV is VALID" : "TRAINING CSV is INVALID");
        printf("Rows: %d\n", training_csv.rows);
        printf("Columns: %d\n", training_csv.columns);
        printf("\n");
        csv_print(training_csv);
    }

    // Importa o arquivo de testes
    Csv testing_csv = csv_import(testing_filepath);
    // Renomeia a tabela CSV
    strcpy(testing_csv.title, "TESTING SET");
    // Verifica se é válido
    is_csv_valid = !!testing_csv.data;


    if (g_verbose)
    {
        puts(is_csv_valid ? "TESTING CSV is VALID" : "TESTING CSV is INVALID");
        printf("Rows: %d\n", testing_csv.rows);
        printf("Columns: %d\n", testing_csv.columns);
        printf("\n");
        csv_print(testing_csv);
    }

    if (testing_csv.columns != training_csv.columns)
    {
        puts("ERROR: Training set and testing set don't match size");
        csv_delete(&training_csv);
        csv_delete(&testing_csv);
        return EXIT_FAILURE;
    }

    // Converter o CSV de treino em um array de KnnDP
    KnnDP *dataset = knn_dataset_from_csv(training_csv);
    unsigned int dataset_s = training_csv.rows;
    unsigned int n = training_csv.columns - 1;
    csv_delete(&training_csv);

    // Converter o CSV de testes em um array de KnnDP
    KnnDP *testset = knn_dataset_from_csv(testing_csv);
    unsigned int testset_s = testing_csv.rows;
    csv_delete(&testing_csv);

    if (g_verbose)
    {
        puts("TRAINING SET:");
        knn_dataset_print(dataset, dataset_s, n);

        puts("TESTING SET:");
        knn_dataset_print(testset, testset_s, n);
    }

    // Extrai todas as labels do dataset
    KnnLL labels = knn_get_labels(dataset, dataset_s);
    // Converte para int
    int *labels_i = malloc(sizeof(int) * labels.count);
    int labels_s = labels.count;
    for (int i = 0; i < labels_s; i++)
    {
        labels_i[i] = labels.labels[i];
    }
    free(labels.labels);

    KnnLabel class;
    KnnDA da;

    unsigned int assertions = 0;

    ConfusionMatrix cm = cm_new(labels.count);
    cm_set_labels(&cm, labels_i);

    switch (distance_algorithm)
    {
        case 'C':
            da = Chebyshev;
            break;

        case 'M':
            da = Minkowski;
            break;
        default:
        case 'E':
            da = Euclidian;
            break;
    }
    for (int i = 0; i < testset_s; i++)
    {
        class = knn_classify(testset + i, dataset, dataset_s, n, k, da, r);
        if (cm_inc(&cm, (int)class, (int)testset[i].label)) assertions++;
    }

    printf("Accuracy: %.2f (%d/%d)\n", (float)assertions / (float)testset_s, assertions, testset_s);
    cm_print(&cm);

    free(labels_i);
    cm_delete(&cm);
    knn_dataset_delete(dataset, dataset_s);
    knn_dataset_delete(testset, testset_s);
    return EXIT_SUCCESS;
}

void print_help ()
{
    puts("Usage: knn [--verbose|-v] [PARAMS]");
    puts("Classify a datapoint or a dataset based on a training dataset using K-Nearest Neighbour algorithm");
    printf("\n");
    puts("  -v, --verbose\t\t\tprints details about the execution");
    printf("\n");
    puts("PARAMS");
    puts("If no params are specified, configurations will be imported from config.txt in the current directory");
    puts("  -A=<distance_algorithm>\tan uppercase letter identifying one of the supported algorithms");
    puts("  -D=<trainingset_path>\t\tpath to training set");
    puts("  -K=<k_neighbours>\t\tnumber of neighbours to be accounted");
    puts("  -O=<result_path>\t\tfile with result output");
    puts("  -R=<p-norm>\t\t\tMinkowski norm");
    puts("  -T=<testingset_path>\t\tpath to testing set");
}