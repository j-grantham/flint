#include <stdio.h>
#include <stdlib.h>
#include "profiler.h"
#include "flint.h"
#include "fmpz_mat.h"
#include "fmpz.h"
#include "ulong_extras.h"

typedef struct
{
    slong m;
    slong n;
    slong k;
    int algorithm;
    slong bits;
} mat_mul_t;


void sample(void * arg, ulong count)
{
    mat_mul_t * params = (mat_mul_t *) arg;
    slong i, n = params->n, m = params->m ;
    slong bits = params->bits;
    int algorithm = params->algorithm;

    flint_rand_t rnd;
    fmpz_mat_t A, C;
    FLINT_TEST_INIT(state);
    

    fmpz_mat_init(A, m, n);
    fmpz_mat_init(C, m, n);

    fmpz_mat_randbits(A, state, bits);

    prof_start();

    if (algorithm == 0)
        for (i = 0; i < count; i++)
            fmpz_mat_mul(C, A, A);
    else if (algorithm == 1)
        for (i = 0; i < count; i++)
            fmpz_mat_sqr(C, A);
    

    prof_stop();

    fmpz_mat_clear(A);
    fmpz_mat_clear(C);
    
    flint_randclear(state);
}

int main(void)
{
    double min_default, min_classical, max;
    mat_mul_t params;
    slong bits, dim;

    for (bits = 1; bits <=2000; bits = (slong) ((double) bits) + 100)
    {
        params.bits = bits;

        flint_printf("bits = %wd :\n", params.bits);

        for (dim = 1; dim <= 312; dim = (slong) ((double) dim * 2.3) + 2)
        {
            params.n = dim;
            params.m = dim;

            params.algorithm = 0;
            prof_repeat(&min_default, &max, sample, &params);

            params.algorithm = 1;
            prof_repeat(&min_classical, &max, sample, &params);


            flint_printf("dim = %wd fmpz_mat_mul : %.2f fmpz_mat_sqr : %.2f         ", dim, min_default, min_classical);
            if (min_default < 0.6*min_classical)
                flint_printf("BAD! \n");
            else if(min_default <= min_classical)
                flint_printf("OK! \n");
            else if (min_default > min_classical)
                flint_printf("GREAT! \n");

        }
    }

    return 0;
}
