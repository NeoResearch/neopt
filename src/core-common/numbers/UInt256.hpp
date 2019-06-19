// TODO: THIS CLASS IS A MIRROR OF UInt256!!!!
#ifndef UINT256_HPP
#define UINT256_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <numbers/UIntBase.hpp>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/shelper.h>

namespace neopt {
// TODO: THIS CLASS IS A MIRROR OF UInt256!!!!
/// <summary>
/// This class stores a 160 bit unsigned int, represented as a 20-byte little-endian byte array
/// </summary>
class UInt256 : public UIntBase
  , public IComparable<UInt256>
  , public IEquatable<UInt256>
{
public:
   static UInt256 Zero()
   {
      return UInt256();
   }

   /// <summary>
   /// The empty constructor stores an empty byte array (TODO: not empty...)
   /// </summary>
   UInt256()
     : UIntBase(32)
   {
   }

   /// <summary>
   /// The byte[] constructor invokes base class UIntBase constructor for 20 bytes
   /// </summary>
   UInt256(vbyte value)
     : UIntBase(32, value)
   {
   }

   /// <summary>
   /// Method CompareTo returns 1 if this UInt256 is bigger than other UInt256; -1 if it's smaller; 0 if it's equals
   /// Example: assume this is 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4, this.CompareTo(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) returns 1
   /// </summary>
   int CompareTo(const UInt256& other) const
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
   bool Equals(const UInt256* other)
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
   /// Method ParseNew receives a big-endian hex string and stores as a UInt256 little-endian 20-bytes array
   /// Example: ParseNew("0xa400ff00ff00ff00ff00ff00ff00ff00ff00ff01") should create UInt256 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4
   /// </summary>
   static UInt256 Parse(string value)
   {
      if (shelper::StartsWith(value, "0x"))
         value = shelper::Substring(value, 2);
      if (value.size() != 64)
      {
         std::cout << "UInt256 size is" << value.size() << std::endl;
         NEOPT_EXCEPTION("UInt256 Parse FormatException");
      }
      //throw new FormatException();
      UInt256 UInt256(vhelper::Reverse(shelper::HexToBytes(value)));
      return std::move(UInt256);
   }

   bool operator==(const UInt256& other) const
   {
      return (this->data_bytes == other.data_bytes);
   }

   bool operator!=(const UInt256& other) const
   {
      return !(*this == other);
   }

   /*
      /// <summary>
      /// Method TryParse tries to parse a big-endian hex string and store it as a UInt256 little-endian 20-bytes array
      /// Example: TryParse("0xa400ff00ff00ff00ff00ff00ff00ff00ff00ff01", result) should create result UInt256 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4
      /// </summary>
      public static bool TryParse(string s, out UInt256 result)
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
           result = new UInt256(data.Reverse().ToArray());
           return true;
      }

      /// <summary>
      /// Operator > returns true if left UInt256 is bigger than right UInt256
      /// Example: UInt256(01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) > UInt256 (02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) is true
      /// </summary>
      public static bool operator >(UInt256 left, UInt256 right)
      {
           return left.CompareTo(right) > 0;
      }

      /// <summary>
      /// Operator > returns true if left UInt256 is bigger or equals to right UInt256
      /// Example: UInt256(01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) >= UInt256 (02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) is true
      /// </summary>
      public static bool operator >=(UInt256 left, UInt256 right)
      {
           return left.CompareTo(right) >= 0;
      }

      /// <summary>
      /// Operator > returns true if left UInt256 is less than right UInt256
      /// Example: UInt256(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) < UInt256 (01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) is true
      /// </summary>
      public static bool operator <(UInt256 left, UInt256 right)
      {
           return left.CompareTo(right) < 0;
      }

      /// <summary>
      /// Operator > returns true if left UInt256 is less or equals to right UInt256
      /// Example: UInt256(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) < UInt256 (01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) is true
      /// </summary>
      public static bool operator <=(UInt256 left, UInt256 right)
      {
           return left.CompareTo(right) <= 0;
      }
      */
};
}

#endif
