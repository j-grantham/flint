/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart, Andy Novocin

*****************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

extern double __gmpn_get_d(mp_limb_t *, size_t, size_t, long);

double fmpz_get_d_2exp(long * exp, const fmpz_t f)
{
   fmpz d = *f;

	if (!COEFF_IS_MPZ(d))
   {
      if (d == 0L) 
      {
         (*exp) = 0L;
         return 0.0;
      }
      ulong d_abs = FLINT_ABS(d);
      (*exp) = FLINT_BIT_COUNT(d_abs);
      if (d < 0L) return __gmpn_get_d(&d_abs, 1L, -1L, -*exp);
      else return __gmpn_get_d(&d, 1L, 1L, -*exp);
   } else 
	   return mpz_get_d_2exp(exp, COEFF_TO_PTR(d));
}
