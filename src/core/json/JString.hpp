#ifndef JSTRING_HPP
#define JSTRING_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include "JObject.hpp"
#include <numbers/UIntBase.hpp>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/ITextReader.h>
#include <system/StringReader.hpp>
#include <system/mhelper.h>
#include <system/shelper.h>

namespace neopt {

class JString : public JObject
{
private:
   std::string _s;

public:
   std::string ToString() const
   {
      return _s;
   }

   JString(std::string s)
     : _s{ s }
   {
   }
};
}

#endif
