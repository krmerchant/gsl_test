#include  "gmock/gmock.h"
#include "line_fit.hh"
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <functional>

std::unique_ptr<LineFit> Create(std::type_info _type)
{
 
  if(_type == typeid(NelderMeadLineFit))
  {
    return std::make_unique<NelderMeadLineFit>();
  }
  else
  {
    return nullptr;
  }
 
   //std::unordered_map<std::type_index, std::function<std::unique_ptr<LineFit>>> factoryMap;
   //factoryMap.emplace(std::type_index(typeid(NelderMeadLineFit)), []() {});


   //auto it = factoryMap.find(std::type_index(typeid(_type)));
   //return it->second();
}



class LineTest : public testing::Test
{
  public:
    std::unique_ptr<LineFit> lineFitter_;


};