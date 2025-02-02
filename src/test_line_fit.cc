#include  "gmock/gmock.h"
#include "line_fit.hh"
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <functional>

#include <vector>
#include <tuple>



bool IsNear(double a, double b, double tol)
{
  return std::abs(a - b) < tol;
}

std::unique_ptr<LineFit> Create(const std::type_info& _type)
{
 
  if(_type == typeid(NelderMeadLineFit))
  {
    return std::make_unique<NelderMeadLineFit>();
  }
  else
  {
    return nullptr;
  }
 

}


std::tuple<std::vector<double>, std::vector<double>> GetSimpleLine()
 {
   std::vector<double> x = {0,1};
   std::vector<double> y = {0,1};
   return std::make_tuple(x,y);
 }    




class LineTest : public testing::Test
{
  public:


};


TEST(LineTest, InitNMTest)
{

  std::unique_ptr<LineFit> lineFitter_ = Create(typeid(NelderMeadLineFit));

}
TEST(LineTest, SimpleLineNMTest)
{
  auto [x,y] = GetSimpleLine();
  std::unique_ptr<LineFit> lineFitter_ = Create(typeid(NelderMeadLineFit));
  auto line = lineFitter_->ComputeLine(x,y);
  ASSERT_TRUE(IsNear(line.m,1,0.01));

}
