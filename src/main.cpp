#include <gsl/gsl_multimin.h>
#include <iostream>
#include <math.h>

double
my_f (const gsl_vector *v, void *params)
{
  double b1, b2;
  double *p1 = (double *)params;

  b1 = gsl_vector_get(v, 0);
  b2 = gsl_vector_get(v, 1);


  double cost = pow(p1[0]-(b1*1 + b2), 2) + pow(p1[1]-(b1*2 + b2), 2) + pow(p1[2]-(b1*3 + b2), 2) + pow(p1[3]-(b1*4 + b2), 2) + pow(p1[4]-(b1*5 + b2), 2);

    cost = sqrt(cost);

    return cost;
}




int main(void)
{
  double par[5] = {2.0, 4.0, 6.0, 8.0, 10.0};

  const gsl_multimin_fminimizer_type *T =
    gsl_multimin_fminimizer_nmsimplex2;
  gsl_multimin_fminimizer *s = NULL;
  gsl_vector *ss, *x;
  gsl_multimin_function minex_func;

  size_t iter = 0;
  int status;
  double size;

  /* Starting point */
  x = gsl_vector_alloc (2);
  gsl_vector_set (x, 0, 3.0);
  gsl_vector_set (x, 1, 0.0);

  /* Set initial step sizes to 1 */
  ss = gsl_vector_alloc (2);
  gsl_vector_set_all (ss, 1.0);

  /* Initialize method and iterate */
  minex_func.n = 2;
  minex_func.f = my_f;
  minex_func.params = par;

  s = gsl_multimin_fminimizer_alloc (T, 2);
  gsl_multimin_fminimizer_set (s, &minex_func, x, ss);

  do
    {
      iter++;
      status = gsl_multimin_fminimizer_iterate(s);

      if (status)
        break;

      size = gsl_multimin_fminimizer_size (s);
      status = gsl_multimin_test_size (size, 1e-5);

      if (status == GSL_SUCCESS)
        {
          printf ("converged to minimum at\n");
        }

      printf ("%5d %10.3e %10.3e f() = %7.3f size = %.3f\n",
              iter,
              gsl_vector_get (s->x, 0),
              gsl_vector_get (s->x, 1),
              s->fval, size);
    }
  while (status == GSL_CONTINUE && iter < 100);

  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free (s);

  return status;
}

