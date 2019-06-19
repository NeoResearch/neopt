#ifndef UINTBASE_HPP
#define UINTBASE_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <system/IBinaryReader.h>
#include <system/IBinaryWriter.h>
#include <system/IEquatable.h>
#include <system/IObject.h>
#include <system/ISerializable.h>
#include <system/vhelper.hpp>

namespace neopt {

/// <summary>
/// Base class for little-endian unsigned integers. Two classes inherit from this: UInt160 and UInt256.
/// Only basic comparison/serialization are proposed for these classes. For arithmetic purposes, use BigInteger class.
/// </summary>
class UIntBase : public IEquatable<UIntBase>
  , public ISerializable //, public IObject (TODO: add only if very necessary)
{
protected: // TODO: make private?
   /// <summary>
   /// Storing unsigned int in a little-endian byte array.
   /// </summary>
   vbyte data_bytes;

public:
   /// <summary>
   /// Number of bytes of the unsigned int.
   /// Currently, inherited classes use 20-bytes (UInt160) or 32-bytes (UInt256)
   /// </summary>
   int Size() const
   {
      return (int)data_bytes.size();
   }

protected:
   // data it's automatically initialized with given size.
   UIntBase(int bytes) // TODO: = 0 (default)
     : data_bytes(vbyte(bytes))
   {
   }

   /// <summary>
   /// Base constructor receives the intended number of bytes and a byte array.
   /// </summary>
   UIntBase(int bytes, vbyte value)
   {
      if (value.size() != (unsigned)bytes)
         NEOPT_EXCEPTION("ArgumentException"); //throw new ArgumentException(); // TODO: throw or NOT? exceptions are not good for performance...
      this->data_bytes = value;                // receiving value (use move semantics?)
   }

protected:
   /// <summary>
   /// Deserialize function reads the expected size in bytes from the given BinaryReader and stores in data_bytes array.
   /// </summary>
   virtual void Deserialize(IBinaryReader& reader)
   {
      std::cout << "UIntBase::Deserialize (" << data_bytes.size() << ")" << std::endl;
      std::cout << "Reader size =" << reader.AvailableBytes() << std::endl;
      reader.Read(data_bytes, 0, data_bytes.size());
   }

public:
   /// <summary>
   /// Method Equals returns true if objects are equal, false otherwise
   /// If null is passed as parameter, this method returns false. If it's a self-reference, it returns true.
   /// </summary>
   virtual bool Equals(UIntBase* other)
   {
      if (other == nullptr)
         return false;
      if (this == other)
         return true;
      if (data_bytes.size() != other->data_bytes.size())
         return false;
      return (data_bytes == other->data_bytes);
   }

   /// <summary>
   /// Method Equals returns true if objects are equal, false otherwise
   /// If null is passed as parameter or if it's not a UIntBase object, this method returns false.
   /// </summary>
   // TODO: add only if very necessary!!
   /*
      bool Equals(IObject* obj)
      {
         if (ReferenceEquals(obj, null))
            return false;
         if (!(obj is UIntBase))
            return false;
         return this.Equals((UIntBase)obj);
      }
      */

   /// <summary>
   /// Method GetHashCode returns a 32-bit int representing a hash code, composed of the first 4 bytes.
   /// </summary>
   virtual int GetHashCode()
   {
      return IObject::ToInt32(data_bytes, 0);
   }

   // cannot forward declare these... use nhelper? TODO
   /*
   /// <summary>
   /// Method Parse receives a big-endian hex string and stores as a UInt160 or UInt256 little-endian byte array
   /// Example: Parse("0xa400ff00ff00ff00ff00ff00ff00ff00ff00ff01") should create UInt160 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4
   /// </summary>
   static UIntBase* Parse(const string& s)
   {
      if (s.size() == 40 || s.size() == 42)
         return UInt160::Parse(s);
      else if (s.size() == 64 || s.size() == 66)
         return UInt256::Parse(s);
      else
         NEOPT_EXCEPTION("FormatException");
      //throw new FormatException();
      return nullptr;
   }
   */

   /// <summary>
   /// Method Serialize writes the data_bytes array into a BinaryWriter object
   /// </summary>
   virtual void Serialize(IBinaryWriter& writer) const
   {
      writer.Write(data_bytes);
   }

   // return copy (TODO: think about it).
   // MerkleTree already uses this as copy... if change this behavior, must update there too, to include a copy there
   // Copy is safer for now. Peformance comes after.
   virtual vbyte ToArray() const
   {
      return data_bytes;
   }
   /*
      /// <summary>
      /// Method ToArray() returns the byte array data_bytes, which stores the little-endian unsigned int
      /// </summary>
      virtual vbyte& ToArray()
      {
         // return copy or reference?
         return data_bytes;
      }
*/

   /*
      /// <summary>
      /// Method ToArray() returns the byte array data_bytes, which stores the little-endian unsigned int
      /// </summary>
      virtual const vbyte& ToArray() const
      {
         // return copy or reference?
         return data_bytes;
      }
*/

   /// <summary>
   /// Method ToString returns a big-endian string starting by "0x" representing the little-endian unsigned int
   /// Example: if this is storing 20-bytes 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4, ToString() should return "0xa400ff00ff00ff00ff00ff00ff00ff00ff00ff01"
   /// </summary>
   virtual string ToString() const
   {
      stringstream ss;
      ss << "0x" << vhelper::ToHexString(vhelper::Reverse(data_bytes));
      return ss.str();
   }

   /*

          /// <summary>
          /// Method TryParse tries to parse a big-endian hex string and stores it as a UInt160 or UInt256 little-endian bytes array
          /// Example: TryParse("0xa400ff00ff00ff00ff00ff00ff00ff00ff00ff01", result) should create result UInt160 01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4
          /// </summary>
          public static bool TryParse<T>(string s, out T result) where T : UIntBase
          {
              int size;
              if (typeof(T) == typeof(UInt160))
                  size = 20;
              else if (typeof(T) == typeof(UInt256))
                  size = 32;
              else if (s.Length == 40 || s.Length == 42)
                  size = 20;
              else if (s.Length == 64 || s.Length == 66)
                  size = 32;
              else
                  size = 0;
              if (size == 20)
              {
                  if (UInt160.TryParse(s, out UInt160 r))
                  {
                      result = (T)(UIntBase)r;
                      return true;
                  }
              }
              else if (size == 32)
              {
                  if (UInt256.TryParse(s, out UInt256 r))
                  {
                      result = (T)(UIntBase)r;
                      return true;
                  }
              }
              result = null;
              return false;
          }

          /// <summary>
          /// Operator == returns true if left UIntBase is equals to right UIntBase
          /// If any parameter is null, it returns false. If both are the same object, it returns true.
          /// Example: UIntBase(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) == UIntBase(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) is true
          /// </summary>
          public static bool operator ==(UIntBase left, UIntBase right)
          {
              if (ReferenceEquals(left, right))
                  return true;
              if (ReferenceEquals(left, null) || ReferenceEquals(right, null))
                  return false;
              return left.Equals(right);
          }

          /// <summary>
          /// Operator != returns true if left UIntBase is not equals to right UIntBase
          /// Example: UIntBase(02ff00ff00ff00ff00ff00ff00ff00ff00ff00a3) != UIntBase(01ff00ff00ff00ff00ff00ff00ff00ff00ff00a4) is true
          /// </summary>
          public static bool operator !=(UIntBase left, UIntBase right)
          {
              return !(left == right);
          }

          */
};
}

#endif
