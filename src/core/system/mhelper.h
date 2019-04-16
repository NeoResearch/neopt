#ifndef MHELPER_H
#define MHELPER_H

// Map Helper: mhelper

// system
#include<map>
#include<sstream>

// neo core
#include<system/types.h>

using namespace std; // TODO: avoid!

namespace neopt
{

// map helper class
class mhelper
{
public:

   template<class T1, class T2>
   static bool ContainsKey(const map<T1,T2>& m, const T1& key)
   {
      return m.count(key);
   }

};

// TODO: define all operators here that are necessary

}

#endif
