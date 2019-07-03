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
   const static BigInteger getMin; // get?
   const static BigInteger One;
   const static BigInteger Zero;
   const static BigInteger MinusOne;

   BigInteger(); // zero
   BigInteger(int32 value);
   BigInteger(const BigInteger& value);

   // byte data in little-endian format
   BigInteger(vbyte data);

   bool operator==(const BigInteger& big);
   bool operator!=(const BigInteger& big);

   bool operator<=(const BigInteger& big);
   bool operator<(const BigInteger& big);

   bool operator>=(const BigInteger& big);
   bool operator>(const BigInteger& big);

   bool IsZero() const;

   vbyte ToByteArray() const;

   int toInt() const;

   int Sign() const;

   static BigInteger Abs(const BigInteger& big);

   static BigInteger Min(const BigInteger& big1, const BigInteger& big2);

   static BigInteger Max(const BigInteger& big1, const BigInteger& big2);

   // operators

   // ~ is the unary one's complement operator -- it flips the bits of its operand.
   BigInteger operator~();

   BigInteger operator& (BigInteger& big2);

   BigInteger operator| (BigInteger& big2);

   BigInteger operator^ (BigInteger& big2);

   BigInteger operator+ (BigInteger& big2);

   BigInteger& operator+= (int i2);

   BigInteger operator- (BigInteger& big2);

   BigInteger& operator-= (int i2);

   // negate (unary)
   BigInteger operator- ();

   BigInteger operator* (BigInteger& big2);

   BigInteger operator/ (BigInteger& big2);

   BigInteger operator% (BigInteger& big2);

   BigInteger& operator<<= (int i2);

   BigInteger& operator>>= (int i2);

   // what is needed here?
};
}

#endif
