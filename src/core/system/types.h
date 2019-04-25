#ifndef TYPES_H
#define TYPES_H

// system includes
#include<vector>
#include<limits>

// core includes
// ... none

namespace neopt
{
// basic types for Neo core

// the simplest chunk of information
typedef unsigned char byte;

// signed short int
typedef short  int16;

// unsigned short int
typedef unsigned short  uint16;

// signed int
typedef int int32;

// unsigned int
typedef unsigned int uint32;

// unsigned long
typedef unsigned long ulong;


// byte array definition
typedef std::vector<byte> vbyte;

#define NEOPT_EXCEPTION(str) { printf("neopt error(%s): %s\n", __func__,  str); exit(1); }

class types
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

}

#endif
