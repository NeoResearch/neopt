#ifndef NHELPER_H
#define NHELPER_H

// Numbers Helper: nhelper

// system
#include<vector>
#include<sstream>
#include<limits>

// neo core
#include<system/types.h>
#include<numbers/UInt160.hpp>

namespace neopt
{

// numbers helper class
class nhelper
{
public:

   template<class T>
   static T MaxValue()
   {
      return std::numeric_limits<T>::max();
   }

   template<class T>
   static T MinValue()
   {
      return std::numeric_limits<T>::min();
   }


};

// TODO: define all operators here that are necessary

}

#endif
