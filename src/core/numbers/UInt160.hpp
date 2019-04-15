#ifndef UINT160_HPP
#define UINT160_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<ISerializable.h>
#include<IEquatable.h>
#include<numbers/UIntBase.hpp>

namespace neopt
{

   /// <summary>
   /// Base class for little-endian unsigned integers. Two classes inherit from this: UInt160 and UInt256.
   /// Only basic comparison/serialization are proposed for these classes. For arithmetic purposes, use BigInteger class.
   /// </summary>
   class UInt160 //: public UIntBase//, public IEquatable<UInt160>
   {
   public:
      virtual void mynumber()
      {

      }
   };
}

#endif
