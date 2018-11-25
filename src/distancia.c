#include "distancia.h"
#include <stdlib.h>
#include <math.h>

float *_distancia_maxf (unsigned int n, float *list)
{
    float *bigger = list;

    for (int i = 1; i < n; i++)
    {
        if (*(list + i) > *bigger)
        {
            bigger = list + i;
        }
    }

    return bigger;
}

float distancia_euclidiana (unsigned int n, float *p, float *q)
{
    float acc = 0.0;

    for (int i = 0; i < n; i++)
    {
        acc += powf(p[i] - q[i], 2.0);
    }

    return sqrtf(acc);
}

float distancia_chebyshev (unsigned int n, float *p, float *q)
{
    float *dist_axis = malloc(sizeof(float) * n);
    float distancia;

    for (int i = 0; i < n; i++)
    {
        *(dist_axis + i) = fabsf(*(p + i) - *(q + i));
    }

    distancia = *(_distancia_maxf(n, dist_axis));

    free(dist_axis);

    return distancia;
}

float distancia_minkowski (unsigned int n, float *p, float *q, float r)
{
    float acc = 0.0;

    for (int i = 0; i < n; i++)
    {
        acc += powf(fabsf(p[i] - q[i]), r);
    }

    return powf(acc, 1.0 / r);
}
