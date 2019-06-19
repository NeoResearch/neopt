#ifndef IEQUATABLE_HPP
#define IEQUATABLE_HPP

// c++ standard part
#include <vector>

// neopt core part
#include "types.h"

namespace neopt {
template<class T>
class IEquatable
{
public:
   // This class can be used as CRTP: the Curiously Recurring Template Pattern

   // Equals: returns true if this object is equals to other
   virtual bool Equals(const T* other) = 0;
};
}

#endif
