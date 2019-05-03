#ifndef NEO_BIGINTEGER_H
#define NEO_BIGINTEGER_H

// c++ standard part
// ... none

// neopt core part
#include <system/types.h>

// partially ported from neo-hypervm and from original specification:
// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs

// this class is intended to be a general interface, allowing different implementations on different languages

namespace neopt {
class BigInteger
{
public:
   const static BigInteger Min;
   const static BigInteger One;
   const static BigInteger Zero;
   const static BigInteger MinusOne;

   BigInteger(int32 value);
   BigInteger(const BigInteger& value);

   // what is needed here?
};
}

#endif
