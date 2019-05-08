#ifndef STRINGREADER_HPP
#define STRINGREADER_HPP

// system includes
#include <algorithm>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

// neopt core part
#include "ITextReader.h"
#include <system/types.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class StringReader : public ITextReader
{
private:
   istream* input{ nullptr };

public:
   // string-based constructor
   StringReader(string s)
     : input{ new istringstream(s) }
   {
   }

   virtual ~StringReader()
   {
      if (input)
         delete input;
   }

   virtual char Read()
   {
      int x = input->get();

      if (x <= 0)
         NEOPT_EXCEPTION("StringReader Conversion Error get Char");

      return (char)x;
   }

   // reads data from this buffer and writes on 'out'
   virtual int Read(char* out, int index, int count)
   {
      for(unsigned i=0; i<count; i++)
      {
         char c = Read();
         out[index+i] = c;
      }
      // TODO: may fail to read enough here!
      return count;
   }

   virtual char Peek() const
   {
      if (input->eof())
         return '\0';

      istream* cinput = const_cast<istream*>(this->input);

      int x = cinput->peek();

      if (cinput->fail()) {
         NEOPT_EXCEPTION("StringReader Peek Failed!");
      }

      if (x <= 0)
         NEOPT_EXCEPTION("StringReader Conversion Char Failed!");

      return (char)x;
   }
};
}

#endif
