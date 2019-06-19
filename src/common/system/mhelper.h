#ifndef NEOPT_MHELPER_H
#define NEOPT_MHELPER_H

// Map Helper: mhelper

// system
#include <map>
#include <sstream>

// neo core
#include "types.h"

namespace neopt {

// map helper class
class mhelper
{
public:
   template<class T1, class T2>
   static bool ContainsKey(const std::map<T1, T2>& m, const T1& key)
   {
      return m.count(key);
   }
};

// TODO: define all operators here that are necessary

}

#endif
