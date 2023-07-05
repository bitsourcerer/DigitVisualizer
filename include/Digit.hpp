#ifndef DIGIT_HPP_INCLUDED
#define DIGIT_HPP_INCLUDED

#define MNIST_SQUARE_DIMENSION 25
#include <array>
#include <iostream>
//#include <iomanip>

namespace config {

const unsigned dim = 28;
const unsigned pixel_count = dim * dim;

}

using namespace config;

template <typename T> using Array = std::array<T, config::pixel_count>;
using DigitArray = Array<unsigned>;

class DigitWriter;

class Digit
{
  friend std::ostream& operator<<(std::ostream&, const Digit&);
  friend class DigitWriter;

public:
  Digit() : value(888), representation() { }
  Digit(int v, const DigitArray &pixels) : value(v), representation(pixels) { }

private:
  int value;
  DigitArray representation;
};

std::ostream& operator<<(std::ostream &os, const Digit &obj)
{
  using config::dim;
  os << "VALUE : " << obj.value << std::endl;
  for(unsigned i = 0; i < dim; ++i)
  {
    for(unsigned j = 0; j < dim; ++j)
      os << (obj.representation[dim*i + j] == 0 ? "-" : "#");
    //os << '\n';
    if(i != dim-1) os << '\n';
  }
  return os;
}

#endif // DIGIT_HPP_INCLUDED
