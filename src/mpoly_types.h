/*
    Copyright (C) 2023, 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#ifndef MPOLY_TYPES_H
#define MPOLY_TYPES_H

#include "flint.h"
#include "fmpz_mod_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MPOLY_MIN_BITS (UWORD(8))    /* minimum number of bits to pack into */

typedef enum {
    ORD_LEX,
    ORD_DEGLEX,
    ORD_DEGREVLEX
} ordering_t;

#define MPOLY_NUM_ORDERINGS 3

typedef struct
{
    slong nvars;    /* number of variables */
    slong nfields;  /* number of fields in exponent vector */
    ordering_t ord; /* monomial ordering */
    int deg;        /* is ord a degree ordering? */
    int rev;        /* is ord a reversed ordering? */
    slong lut_words_per_exp[FLINT_BITS];
    unsigned char lut_fix_bits[FLINT_BITS]; /* FLINT_BITS < 256 */
} mpoly_ctx_struct;

typedef mpoly_ctx_struct mpoly_ctx_t[1];

typedef struct
{
    mpoly_ctx_t minfo;
    nmod_t mod;
}
nmod_mpoly_ctx_struct;

typedef nmod_mpoly_ctx_struct nmod_mpoly_ctx_t[1];

typedef struct
{
    mpoly_ctx_t minfo;
}
fmpz_mpoly_ctx_struct;

typedef fmpz_mpoly_ctx_struct fmpz_mpoly_ctx_t[1];

typedef struct
{
    fmpz_mpoly_ctx_t zctx;
}
fmpq_mpoly_ctx_struct;

typedef fmpq_mpoly_ctx_struct fmpq_mpoly_ctx_t[1];

typedef struct
{
    mpoly_ctx_t minfo;
    fmpz_mod_ctx_t ffinfo;
}
fmpz_mod_mpoly_ctx_struct;

typedef fmpz_mod_mpoly_ctx_struct fmpz_mod_mpoly_ctx_t[1];

typedef struct {
    slong elem_size;
    const void * ctx;
    void (*init)(void *, const void *);
    void (*clear)(void *, const void *);
    int (*is_zero)(const void *, const void *);
    void (*zero)(void *, const void *);
    void (*one)(void *, const void *);
    void (*set_fmpz)(void *, const fmpz_t, const void *);
    void (*set)(void *, const void *, const void *);
    void (*swap)(void *, void *, const void *);
    void (*neg)(void *, const void *, const void *);
    void (*add)(void *, const void *, const void *, const void *);
    void (*sub)(void *, const void *, const void *, const void *);
    void (*mul_fmpz)(void *, const void *, const fmpz_t, const void *);
    void (*mul)(void *, const void *, const void *, const void *);
    void (*divexact)(void *, const void *, const void *, const void *);
    int (*divides)(void *, const void *, const void *, const void *);
    int (*pow_fmpz)(void *, const void *, const fmpz_t, const void *);
    slong (*length)(const void *, const void *);
} mpoly_void_ring_t[1];

typedef struct
{
    ulong * Amax_exp;
    ulong * Amin_exp;
    ulong * Astride;
    slong * Adeflate_deg;
    slong * Alead_count;
    slong * Atail_count;

    ulong * Bmax_exp;
    ulong * Bmin_exp;
    ulong * Bstride;
    slong * Bdeflate_deg;
    slong * Blead_count;
    slong * Btail_count;

    ulong * Gmin_exp;
    ulong * Abarmin_exp;
    ulong * Bbarmin_exp;
    ulong * Gstride;
    slong * Gterm_count_est;
    slong * Gdeflate_deg_bound;

    flint_bitcnt_t Gbits, Abarbits, Bbarbits;

    slong mvars;
    slong Adeflate_tdeg;
    slong Bdeflate_tdeg;

    double Adensity;
    double Bdensity;

    double hensel_time, brown_time, zippel_time, zippel2_time;
    slong * hensel_perm, * brown_perm, * zippel_perm, * zippel2_perm;
    unsigned int can_use;
    int Gdeflate_deg_bounds_are_nice; /* all of Gdeflate_deg_bound came from real gcd computations */

    char * data;
} mpoly_gcd_info_struct;

typedef mpoly_gcd_info_struct mpoly_gcd_info_t[1];

#ifdef __cplusplus
}
#endif

#endif /* MPOLY_TYPES_H */
