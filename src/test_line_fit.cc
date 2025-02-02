#include  "gmock/gmock.h"
#include "line_fit.hh"
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <functional>

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



class LineTest : public testing::Test
{
  public:
    std::unique_ptr<LineFit> lineFitter_;

};


TEST(LineTest, InitNMTest)
{

    std::unique_ptr<LineFit> lineFitter_ = Create(typeid(NelderMeadLineFit));

}
