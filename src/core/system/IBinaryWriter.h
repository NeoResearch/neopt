#ifndef NEOPT_IBINARYWRITER_H
#define NEOPT_IBINARYWRITER_H

// neopt core part
#include "ISerializable.h"
#include "types.h"

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

// Visual C++
// include intrin.h
// GCC bit inverters (very fast, assembly speed)
//#include<byteswap.h>
//int32_t __builtin_bswap32 (int32_t x)
//int64_t __builtin_bswap64 (int64_t x)
// doing manually for now

namespace neopt {

class IBinaryWriter
{
public:
   // most important method, how to write a single byte?
   virtual void Write(byte v) = 0;

   // writes data directly from vector
   virtual void Write(const vbyte& data)
   {
      for (unsigned i = 0; i < data.size(); i++)
         this->Write(data[i]);
   }

   // Writes a region of a byte array to the current stream
   virtual void Write(const vbyte& data, int index, int count)
   {
      vbyte part(data.begin() + index, data.begin() + index + count);
      this->Write(part);
   }

   virtual void Write(ushort v)
   {
      Write((byte)(((v >> 0) << 8) >> 8));
      Write((byte)(((v >> 8) << 8) >> 8));
   }

   virtual void Write(short v)
   {
      Write(ushort(v));
   }

   virtual void Write(uint v)
   {
      Write((byte)(((v >> 0) << 24) >> 24));
      Write((byte)(((v >> 8) << 24) >> 24));
      Write((byte)(((v >> 16) << 24) >> 24));
      Write((byte)(((v >> 24) << 24) >> 24));
   }

   virtual void Write(int v)
   {
      Write(uint(v));
   }

   virtual void Write(ulong v)
   {
      Write((byte)(((v >> 0) << 56) >> 56));
      Write((byte)(((v >> 8) << 56) >> 56));
      Write((byte)(((v >> 16) << 56) >> 56));
      Write((byte)(((v >> 24) << 56) >> 56));
      Write((byte)(((v >> 32) << 56) >> 56));
      Write((byte)(((v >> 40) << 56) >> 56));
      Write((byte)(((v >> 48) << 56) >> 56));
      Write((byte)(((v >> 56) << 56) >> 56));
   }

   virtual void Write(long v)
   {
      Write(ulong(v));
   }

   // writes var bytes on vector
   virtual void WriteVarBytes(const vbyte& value)
   {
      this->WriteVarInt(value.size());
      this->Write(value);
   }

   virtual void Write(const ISerializable& value)
   {
      value.Serialize(*this);
   }

   //  TODO: port to C# (only C++)
   virtual void Write(const std::vector<vbyte>& value)
   {
      this->WriteVarInt(value.size());
      for (unsigned i = 0; i < value.size(); i++) {
         this->WriteVarBytes(value[i]);
      }
   }

   template<class T>
   static void WriteArray(IBinaryWriter& writer, const std::vector<T>& value)
   {
      writer.WriteVarInt(value.size());
      for (unsigned i = 0; i < value.size(); i++) {
         value[i].Serialize(writer);
      }
   }

   ///virtual void Flush() = 0; // don't know if actually needed

   virtual void WriteVarInt(long value)
   {
      if (value < 0)
         NEOPT_EXCEPTION("IBinaryWriter::WriteVarInt ArgumentOutOfRangeException");
      if (value < 0xFD) {
         this->Write((byte)value);
      } else if (value <= 0xFFFF) {
         this->Write((byte)0xFD);
         this->Write((ushort)value);
      } else if (value <= 0xFFFFFFFF) {
         this->Write((byte)0xFE);
         this->Write((uint)value);
      } else {
         this->Write((byte)0xFF);
         this->Write(value);
      }
   }

   virtual int CountBytes() const
   {
      return -1; // number of bytes on buffer, or -1 if unknown
   }
};
}

#endif
