#ifndef LINE_FIT_HH_
#define LINE_FIT_HH_

#include <vector>
#include <gsl/gsl_multimin.h>

struct Line
{
  /**
   * @brief simple stupid datastruct:  "y=mx+b"
   * 
   */
  Line(double _m, double _b): m(_m),b(_b){}
  double m;  
  double b;
};

/**
 * @brief Strategy Class
 * Compute a basic linear fit with a series of 2D points
 * 
 * 
 */
class LineFit
{
  public:
    LineFit(){};
    virtual Line ComputeLine(std::vector<double> _x, std::vector<double> _y) const = 0;

};


class NelderMeadLineFit : public LineFit
{


  public: 
   NelderMeadLineFit(){};
   Line ComputeLine(std::vector<double> _x, std::vector<double> _y) const
   {

    auto [m,b] = RunOptimizer(_x,_y);
    return Line(m,b);
   }


  struct Params
  {
    std::vector<double> x; 
    std::vector<double> y; 
    Params(std::vector<double>_x, std::vector<double> _y):x(_x),y(_y){}

  };



   std::tuple<double,double> RunOptimizer(std::vector<double> _x, std::vector<double> _y) const
   {
     const gsl_multimin_fminimizer_type *T =
         gsl_multimin_fminimizer_nmsimplex2;
     gsl_multimin_fminimizer *s = NULL;
     gsl_vector *ss, *x;
     gsl_multimin_function minex_func;

    
     size_t iter = 0;
     int status;
     double size;

     /* Starting point */
     x = gsl_vector_alloc(2); //m and b
     gsl_vector_set(x, 0, 0.0);
     gsl_vector_set(x, 1, 0.0);

     /* Set initial step sizes to 1 */
     ss = gsl_vector_alloc(2);
     gsl_vector_set_all(ss, 1.0);

     /* Initialize method and iterate */

     minex_func.n = 2;
     minex_func.f = [](const gsl_vector *modelParams, void *params) 
     {
       double m =  gsl_vector_get(modelParams, 0);
       double b =  gsl_vector_get(modelParams, 1);
       double cost = 0;
       Params * data = static_cast<Params*>(params);
       for (int i = 0; i < data->x.size() ; i++)
       {
        double fit = m*data->x[i] + b;
        cost+= std::abs(fit - data->y[i]);

       }
      return cost;

     };

     Params params(_x,_y);
     minex_func.params = &params;

     s = gsl_multimin_fminimizer_alloc(T, 2);
     gsl_multimin_fminimizer_set(s, &minex_func, x, ss);

     do
     {
       iter++;
       status = gsl_multimin_fminimizer_iterate(s);

       if (status)
         break;

       size = gsl_multimin_fminimizer_size(s);
       status = gsl_multimin_test_size(size, 1e-5);

       if (status == GSL_SUCCESS)
       {
         printf("converged to minimum at\n");
       }

       printf("%5d %10.3e %10.3e f() = %7.3f size = %.3f\n",
              iter,
              gsl_vector_get(s->x, 0),
              gsl_vector_get(s->x, 1),
              s->fval, size);
     } while (status == GSL_CONTINUE && iter < 1000);
    


     double m = gsl_vector_get(s->x, 0);
     double b = gsl_vector_get(s->x, 1);
     gsl_vector_free(x);
     gsl_vector_free(ss);
     gsl_multimin_fminimizer_free(s);
     return std::make_tuple(m, b);
   }

};

#endif 