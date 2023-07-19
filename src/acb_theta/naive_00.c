/*
    Copyright (C) 2023 Jean Kieffer

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_theta.h"

static void
worker_dim0(acb_ptr th, const acb_t term, slong* coords, slong g, ulong ab,
    slong ord, slong prec, slong fullprec)
{
    acb_add(th, th, x, fullprec);
}

void
acb_theta_naive_00(acb_ptr th, acb_srcptr z, slong nb_z, const acb_mat_t tau, slong prec)
{
    slong g = acb_mat_nrows(tau);
    acb_theta_eld_t E;
    acb_theta_precomp_t D;
    arf_t eps;
    acb_ptr c;
    arb_ptr u;
    acb_ptr new_z;
    slong ord = 0;
    slong nb = 1;
    slong k;

    acb_theta_eld_init(E, g, g);
    acb_theta_precomp_init(D, nb_z, g);
    arf_init(eps);
    c = _acb_vec_init(nb_z);
    u = _arb_vec_init(nb_z);
    new_z = _acb_vec_init(g * nb_z);

    arf_one(eps);
    arf_mul_2exp_si(eps, eps, -prec);
    acb_theta_naive_ellipsoid(E, new_z, c, u, ord, z, nb_z, tau, eps, prec);
    prec = acb_theta_naive_fullprec(E, prec);
    acb_theta_precomp_set(D, new_z, tau, E, prec);

    for (k = 0; k < nb_z; k++)
    {
        acb_theta_naive_worker(&th[k], nb, &c[k], &u[k], E, D, k, ab, ord,
            prec, worker_dim0);
    }

    acb_theta_eld_clear(E);
    acb_theta_precomp_clear(D);
    arf_clear(eps);
    _acb_vec_clear(c, nb_z);
    _arb_vec_clear(u, nb_z);
    _acb_vec_clear(new_z, g * nb_z);
}
