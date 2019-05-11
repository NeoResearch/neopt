#ifndef NEOPT_TYPES_H
#define NEOPT_TYPES_H

// system includes
#include <limits>
#include <vector>

// core includes
// ... none

namespace neopt {
// basic types for Neo core

// the simplest chunk of information
// TODO: migrate to C++17 byte type
typedef unsigned char byte;

// half byte: nibble
//typedef byte nibble;
//typedef uint_least8_t nibble;
struct nibble
{
   nibble()
     : v{ 0X0 }
   {
   }

   nibble(byte b)
     : v{ b }
   {
   }

   operator byte() const
   {
      return (byte)v;
   }

   /*
   operator int() const
   {
      return (int)v;
   }
   */

   unsigned char v;
   //unsigned char v : 4; // better not mess with bits and unaligned ints...
};

// signed short int
typedef short int16;

// unsigned short int
typedef unsigned short uint16;

// signed int
typedef int int32;

// unsigned int
typedef unsigned int uint32;

// unsigned long
typedef unsigned long ulong;

// =================
// array definitions
// -----------------

// byte array definition
typedef std::vector<byte> vbyte;

// nibble array definition
typedef std::vector<nibble> vnibble;

#define NEOPT_EXCEPTION(str)                          \
   {                                                  \
      printf("neopt error(%s): %s\n", __func__, str); \
      exit(1);                                        \
   }

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

template<typename T>
struct MakeStatic
{
   // the const guarantees that 'global state' is read-only for static purposes only
   static const T& object()
   {
      static T t;
      return t;
   }
};

/*
// Example static Singleton Class
class MyStaticSingletonClass final
{
  public:
    // const must be added to ensure global state is read-only
    // this is not a standard singleton, and it is much safer
    void hi() const 
    {
    }
  private:
    friend struct MakeStatic<MyStaticSingletonClass>;
};
*/

} // namespace neopt

#endif
