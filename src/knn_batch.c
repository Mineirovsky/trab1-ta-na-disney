#include "knn.h"
#include "result.h"
#include "config_file.h"
#include "distancia.h"
#include <stdlib.h>
#include <string.h>

Result *knn_batch(
    unsigned int n,
    KnnDP *dataset,
    unsigned int dataset_s,
    KnnDP *testset,
    unsigned int testset_s,
    Conf conf
)
{
    Result *results = malloc(sizeof(Result) * conf.runs);

    // Aloca memória para os vetores das predições
    for (int i = 0; i < conf.runs; i++)
    {
        results[i].predictions = malloc(sizeof(KnnLabel) * testset_s);
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

    unsigned int assertions;

    ConfusionMatrix cm;

    ConfRS *rs;
    for (int i = 0; i < conf.runs; i++)
    {
        assertions = 0;
        cm = cm_new(labels.count);
        cm_set_labels(&cm, labels_i);

        rs = conf.run_setups + i;
        switch (rs->algorithm)
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

        for (int j = 0; j < testset_s; j++)
        {
            class = results[i].predictions[j] = knn_classify(testset + j, dataset, dataset_s, n, rs->k, da, rs->r);
            if (cm_inc(&cm, (int)class, (int)testset[j].label)) assertions++;
        }

        results[i].assertions = assertions;
        results[i].accuracy = (float) assertions / (float) testset_s;
        results[i].cm = cm;
        results[i].samples = testset_s;
    }

    free(labels_i);
    return results;
}
