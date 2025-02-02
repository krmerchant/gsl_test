#ifndef LINE_FIT_HH_
#define LINE_FIT_HH_

#include <vector>
#include <vector>

struct Line
{
  /**
   * @brief simple stupid datastruct:  "y=mx+b"
   * 
   */
  Line(double _m, double _b): m_(_m),b_(_b){}

  private:
    double m_;  
    double b_;
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

  protected:
    virtual Line ComputeLine(std::vector<double> _x, std::vector<double> _y) = 0;

};


class NelderMeadLineFit : public LineFit
{


  public: 
   NelderMeadLineFit(){};
   Line ComputeLine(std::vector<double> _x, std::vector<double> _y)
   {
    return Line(0,0);
   }

};




#endif 