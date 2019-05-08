#ifndef JBOOLEAN_HPP
#define JBOOLEAN_HPP

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

class JBoolean : public JObject
{
private:
   bool _b;

public:
   JBoolean(bool b)
     : _b{ b }
   {
   }

   // ToString()
};
}

#endif
