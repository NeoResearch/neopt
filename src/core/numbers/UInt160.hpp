#ifndef UINT160_HPP
#define UINT160_HPP

// c++ standard part
#include <vector>

// neopt core part
//#include<system/ISerializable.h>
#include <numbers/UIntBase.hpp>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/shelper.h>
#include <system/vhelper.hpp>

namespace neopt {

/// <summary>
/// This class stores a 160 bit unsigned int, represented as a 20-byte little-endian byte array
/// </summary>
class UInt160 : public UIntBase
  , public IComparable<UInt160>
  , public IEquatable<UInt160>
{
public:
   static UInt160 Zero()
   {
      return UInt160();
   }

   /// <summary>
   /// The empty constructor stores an empty byte array (TODO: not empty...)
   /// </summary>
   UInt160()
     : UIntBase(20)
   {
   }

   /// <summary>
   /// The byte[] constructor invokes base class UIntBase constructor for 20 bytes
   /// </summary>
   UInt160(vbyte value)
     : UIntBase(20, value)
   {
   }

   /// <summary>
   /// Method CompareTo returns 1 if this UInt160 is bigger than other UInt160; -1 if it's smaller; 0 if it's equals
   /// Example: assume this is 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4, this.CompareTo(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) returns 1
   /// </summary>
   int CompareTo(const UInt160& other) const
   {
      const vbyte& vother = other.data_bytes;
      const vbyte& vthis = this->data_bytes;
      if (vother.size() != vthis.size())
         return 1; // or -1 or 0 (TODO ?)
      // TODO: implement and verify this logic (must be little endian!)
      for (int i = int(vother.size()) - 1; i >= 0; i--) {
         if (vthis[i] > vother[i])
            return 1;
         if (vthis[i] < vother[i])
            return -1;
      }

      return 0;
   }

   /// <summary>
   /// Method Equals returns true if objects are equal, false otherwise
   /// </summary>
   bool Equals(const UInt160* other)
   {
      if (other == nullptr)
         return false;
      // (other == nullptr ? false : CompareTo(*other) == 0) // TODO: make shorter?
      return CompareTo(*other) == 0;
   }

   // TODO: why do I need this?
   bool Equals(const UIntBase* other)
   {
      if (other == nullptr)
         return false;
      // (other == nullptr ? false : CompareTo(*other) == 0) // TODO: make shorter?
      return 1; // TODO: verify //CompareTo(*other) == 0;
   }

   /// <summary>
   /// Method ParseNew receives a big-endian hex string and stores as a UInt160 little-endian 20-bytes array
   /// Example: ParseNew("0xa400ff00ff00ff00ff00ff00ff00ff00ff00ff01") should create UInt160 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4
   /// </summary>
   static UInt160 Parse(string value)
   {
      if (shelper::StartsWith(value, "0x"))
         value = shelper::Substring(value, 2);
      if (value.size() != 40)
         NEOPT_EXCEPTION("UInt160 Parse FormatException");
      //throw new FormatException();
      UInt160 uint160(vhelper::Reverse(shelper::HexToBytes(value)));
      return std::move(uint160);
   }

   /*
      /// <summary>
      /// Method TryParse tries to parse a big-endian hex string and store it as a UInt160 little-endian 20-bytes array
      /// Example: TryParse("0xa400ff00ff00ff00ff00ff00ff00ff00ff00ff01", result) should create result UInt160 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4
      /// </summary>
      public static bool TryParse(string s, out UInt160 result)
      {
           if (s == null)
           {
               result = null;
               return false;
           }
           if (s.StartsWith("0x"))
               s = s.Substring(2);
           if (s.Length != 40)
           {
               result = null;
               return false;
           }
           byte[] data = new byte[20];
           for (int i = 0; i < 20; i++)
               if (!byte.TryParse(s.Substring(i * 2, 2), NumberStyles.AllowHexSpecifier, null, out data[i]))
               {
                   result = null;
                   return false;
               }
           result = new UInt160(data.Reverse().ToArray());
           return true;
      }

      /// <summary>
      /// Operator > returns true if left UInt160 is bigger than right UInt160
      /// Example: UInt160(01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) > UInt160 (02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) is true
      /// </summary>
      public static bool operator >(UInt160 left, UInt160 right)
      {
           return left.CompareTo(right) > 0;
      }

      /// <summary>
      /// Operator > returns true if left UInt160 is bigger or equals to right UInt160
      /// Example: UInt160(01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) >= UInt160 (02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) is true
      /// </summary>
      public static bool operator >=(UInt160 left, UInt160 right)
      {
           return left.CompareTo(right) >= 0;
      }

      /// <summary>
      /// Operator > returns true if left UInt160 is less than right UInt160
      /// Example: UInt160(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) < UInt160 (01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) is true
      /// </summary>
      public static bool operator <(UInt160 left, UInt160 right)
      {
           return left.CompareTo(right) < 0;
      }

      /// <summary>
      /// Operator > returns true if left UInt160 is less or equals to right UInt160
      /// Example: UInt160(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) < UInt160 (01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) is true
      /// </summary>
      public static bool operator <=(UInt160 left, UInt160 right)
      {
           return left.CompareTo(right) <= 0;
      }
      */
};
}

#endif
