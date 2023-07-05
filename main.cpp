#include "include/DigitWriter.h"
using namespace std;

int main(int argc, char* argv[])
{
  ofstream file("digits.txt", ifstream::app);
  DigitStream ds("mnist_test.txt");

  DigitWriter* dw = nullptr;

  if(argc >= 2)
    dw = new DigitWriter(argv[1]);
  else
    dw = new DigitWriter("mnist_test.txt");
  dw->run();

  delete(dw);
  file.close();
  return 0;
}
