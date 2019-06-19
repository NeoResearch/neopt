#ifndef ICOMPARABLE_HPP
#define ICOMPARABLE_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <system/types.h>

namespace neopt {
template<class T>
class IComparable
{
public:
   // This class can be used as CRTP: the Curiously Recurring Template Pattern

   // CompareTo: compares and returns an integer
   virtual int CompareTo(const T& other) const = 0;
};
}

#endif
