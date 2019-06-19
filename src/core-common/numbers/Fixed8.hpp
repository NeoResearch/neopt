#ifndef FIXED8_H
#define FIXED8_H

// c++ standard part
//#include<decimal/decimal>

// neopt core part
#include <numbers/BigInteger.h>
#include <numbers/nhelper.h>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/printable.h>
#include <system/types.h>

// TODO: perhaps this class should be an interface too... just like BigInteger.
// if this is fully compatible, let's keep this way

namespace neopt {
/// <summary>
/// Accurate to 10^-8 64-bit fixed-point numbers minimize rounding errors.
/// By controlling the accuracy of the multiplier, rounding errors can be completely eliminated.
/// </summary>
class Fixed8 : public IComparable<Fixed8>
  , public IEquatable<Fixed8>
  , public ISerializable //IFormattable,
{
private:
   static const long D = 100000000; // 100M

protected:
   long value;

public:
   static const Fixed8 MaxValue()
   {
      return Fixed8(types::MaxValue<long>());
   }

   static const Fixed8 MinValue()
   {
      return Fixed8(types::MinValue<long>());
   }

   static const Fixed8 One()
   {
      return Fixed8(D);
   }

   static const Fixed8 Satoshi()
   {
      return Fixed8(1);
   }

   static const Fixed8 Zero()
   {
      return Fixed8();
   }

   int Size() const
   {
      // hope it's 8 bytes...
      return sizeof(long);
   }

   Fixed8(long data = 0)
     : value(data)
   {
   }

   Fixed8 Abs()
   {
      if (value >= 0)
         return *this;

      return Fixed8(-value);
   }

   Fixed8 Ceiling()
   {
      long remainder = value % D;
      if (remainder == 0)
         return *this;
      if (remainder > 0)
         return Fixed8(value - remainder + D);
      else
         return Fixed8(value - remainder);
   }

   int CompareTo(const Fixed8& other) const
   {
      if (value == other.value)
         return 0;
      return (value < other.value) ? -1 : 1;
   }

   void Deserialize(IBinaryReader& reader)
   {
      value = reader.ReadInt64();
   }

   bool Equals(const Fixed8* other)
   {
      return value == other->value;
   }

   /*
      bool Equals(object* obj)
      {
         if (!(obj is Fixed8)) return false;
         return Equals((Fixed8)obj);
      }
*/
   /*
      static Fixed8 FromDecimal(decimal value)
      {
         value *= D;
         if (value < long.MinValue || value > long.MaxValue)
             throw new OverflowException();
         return new Fixed8
         {
             value = (long)value
         };
      }
*/
   long GetData()
   {
      return value;
   }

   int GetHashCode()
   {
      return 0; // TODO //value.GetHashCode();
   }

   /*
      static Fixed8 Max(Fixed8 first, params Fixed8[] others)
      {
         foreach (Fixed8 other in others)
         {
             if (first.CompareTo(other) < 0)
                 first = other;
         }
         return first;
      }
*/
   // first has priority on ties
   static Fixed8 Max(const Fixed8& first, const Fixed8& other)
   {
      if (first.CompareTo(other) < 0)
         return other;
      else
         return first;
   }

   // first has priority on ties
   static Fixed8 Min(const Fixed8& first, const Fixed8& other)
   {
      if (first.CompareTo(other) > 0)
         return other;
      else
         return first;
   }

   static Fixed8 Parse(string s)
   {
      NEOPT_EXCEPTION("Not implemented Fixed8 Parse");
      return Fixed8();
      //return FromDecimal(decimal.Parse(s, NumberStyles.Float, CultureInfo.InvariantCulture));
   }

   void Serialize(IBinaryWriter& writer) const
   {
      writer.Write(value);
   }

   //string ToString(string format)
   virtual string ToString() const
   {
      std::stringstream ss;
      ss << this->value / D << ".";
      ss << std::setfill('0') << std::setw(8) << this->value % D;
      return ss.str();
   }

   /*
      static bool TryParse(string s, out Fixed8 result)
      {
         decimal d;
         if (!decimal.TryParse(s, NumberStyles.Float, CultureInfo.InvariantCulture, out d))
         {
             result = default(Fixed8);
             return false;
         }
         d *= D;
         if (d < long.MinValue || d > long.MaxValue)
         {
             result = default(Fixed8);
             return false;
         }
         result = new Fixed8
         {
             value = (long)d
         };
         return true;
      }
*/

   // ========================== OPERATORS

   // overloaded minus (-) operator
   Fixed8 operator-() const
   {
      return std::move(Fixed8(this->value));
   }

   Fixed8 operator/(long y) const
   {
      Fixed8 result(this->value / y);
      return std::move(result);
   }

   bool operator==(const Fixed8& that) const
   {
      return this->value == that.value;
   }

   // TODO: support decimal
   /*
    decimal::decimal64 decimal() const
    {
        return this->value / (decimal::decimal64)D;
    }
*/

   /*
        public static explicit operator long(Fixed8 value)
        {
            return value.value / D;
        }

        public static bool operator ==(Fixed8 x, Fixed8 y)
        {
            return x.Equals(y);
        }

        public static bool operator !=(Fixed8 x, Fixed8 y)
        {
            return !x.Equals(y);
        }

        public static bool operator >(Fixed8 x, Fixed8 y)
        {
            return x.CompareTo(y) > 0;
        }

        public static bool operator <(Fixed8 x, Fixed8 y)
        {
            return x.CompareTo(y) < 0;
        }

        public static bool operator >=(Fixed8 x, Fixed8 y)
        {
            return x.CompareTo(y) >= 0;
        }

        public static bool operator <=(Fixed8 x, Fixed8 y)
        {
            return x.CompareTo(y) <= 0;
        }

        public static Fixed8 operator *(Fixed8 x, Fixed8 y)
        {
            const ulong QUO = (1ul << 63) / (D >> 1);
            const ulong REM = ((1ul << 63) % (D >> 1)) << 1;
            int sign = Math.Sign(x.value) * Math.Sign(y.value);
            ulong ux = (ulong)Math.Abs(x.value);
            ulong uy = (ulong)Math.Abs(y.value);
            ulong xh = ux >> 32;
            ulong xl = ux & 0x00000000fffffffful;
            ulong yh = uy >> 32;
            ulong yl = uy & 0x00000000fffffffful;
            ulong rh = xh * yh;
            ulong rm = xh * yl + xl * yh;
            ulong rl = xl * yl;
            ulong rmh = rm >> 32;
            ulong rml = rm << 32;
            rh += rmh;
            rl += rml;
            if (rl < rml)
                ++rh;
            if (rh >= D)
                throw new OverflowException();
            ulong rd = rh * REM + rl;
            if (rd < rl)
                ++rh;
            ulong r = rh * QUO + rd / D;
            x.value = (long)r * sign;
            return x;
        }

        public static Fixed8 operator *(Fixed8 x, long y)
        {
            x.value = checked(x.value * y);
            return x;
        }

        public static Fixed8 operator /(Fixed8 x, long y)
        {
            x.value /= y;
            return x;
        }

        public static Fixed8 operator +(Fixed8 x, Fixed8 y)
        {
            x.value = checked(x.value + y.value);
            return x;
        }

        public static Fixed8 operator -(Fixed8 x, Fixed8 y)
        {
            x.value = checked(x.value - y.value);
            return x;
        }

        public static Fixed8 operator -(Fixed8 value)
        {
            value.value = -value.value;
            return value;
        }
       */
};
}

#endif
