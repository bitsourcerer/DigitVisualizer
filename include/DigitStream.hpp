#ifndef TEXTSTREAM_HPP_INCLUDED
#define TEXTSTREAM_HPP_INCLUDED

#include "digit.hpp"
#include <fstream>
#include <string>
#include "StackandQueue/Stack.hpp"

//extern unsigned dim;
//extern unsigned pixel_count;

class DigitStream
{
public:
  DigitStream() = default;
  DigitStream(const char* filename) : name(filename), textfile(filename) {
    if(!textfile.is_open()) throw std::runtime_error("Cannot open file: " + std::string(filename));
  }
  DigitStream(const DigitStream &ds) : textfile(ds.name), bookmarks(ds.bookmarks) { ; }
  ~DigitStream() { textfile.close(); }

  Digit next();
  Digit get();
  Digit prev();

  bool HasNext() const { return !textfile.eof(); }
  void AddBookmark();
  std::ifstream::pos_type RemoveBookmark();

private:
  Digit current;
  std::string name;
  std::ifstream textfile;
  //std::istreambuf_iterator<unsigned> file_iter, file_eof;
  Stack<std::ifstream::pos_type> bookmarks;
};

Digit DigitStream::next()
{
  AddBookmark();
  return get();
}

Digit DigitStream::get()
{
  if(!HasNext()) return current;
  DigitArray repr;
  int value;

  textfile >> value;

  for(DigitArray::size_type i = 0; i < repr.size(); ++i)
    textfile >> repr[i];

  current = Digit(value, repr);
  return current;
}

Digit DigitStream::prev()
{
  //if(bookmarks.empty()) return current;
  std::ifstream::pos_type previous = RemoveBookmark();
  textfile.seekg(previous);

  Digit d = get();
  return d;
}

void DigitStream::AddBookmark()
{
  bookmarks.push(textfile.tellg());
}

std::ifstream::pos_type DigitStream::RemoveBookmark()
{
  if(bookmarks.empty()) return std::ifstream::beg;
  return bookmarks.pop();
}

#endif // TEXTSTREAM_HPP_INCLUDED
