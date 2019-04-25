#ifndef IBINARYWRITER_H
#define IBINARYWRITER_H

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

// neopt core part
#include<system/types.h>
#include<system/ISerializable.h>

namespace neopt
{

class IBinaryWriter
{
public:

   // most important method, how to write a single byte?
   virtual void Write(byte v) = 0;

   // writes data directly from vector
   virtual void Write(const vbyte& data)
   {
      for(unsigned i=0; i<data.size(); i++)
         this->Write(data[i]);
   }

   virtual void Write(ushort v)
   {
   }

   virtual void Write(short v)
   {
   }

   virtual void Write(uint v)
   {
   }

   virtual void Write(int v)
   {
   }

   virtual void Write(ulong v)
   {
   }

   virtual void Write(long v)
   {
   }

   // writes var bytes on vector
   virtual void WriteVarBytes(const vbyte& v)
   {

   }


   virtual void Write(ISerializable& value)
   {
      value.Serialize(*this);
   }


   template<class T>
   static void WriteArray(IBinaryWriter& writer, const std::vector<T>& value)
   {
       writer.WriteVarInt(value.size());
       for (unsigned i = 0; i < value.size(); i++)
       {
           value[i].Serialize(writer);
       }
   }

   virtual void Flush() = 0; // don't know if actually needed


   virtual void WriteVarInt(long value)
   {
        if (value < 0)
            NEOPT_EXCEPTION("IBinaryWriter::WriteVarInt ArgumentOutOfRangeException");
        if (value < 0xFD)
        {
            this->Write((byte)value);
        }
        else if (value <= 0xFFFF)
        {
            this->Write((byte)0xFD);
            this->Write((ushort)value);
        }
        else if (value <= 0xFFFFFFFF)
        {
            this->Write((byte)0xFE);
            this->Write((uint)value);
        }
        else
        {
            this->Write((byte)0xFF);
            this->Write(value);
        }
     }
};

}

#endif
