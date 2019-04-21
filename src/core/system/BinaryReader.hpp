#ifndef BINARYREADER_HPP
#define BINARYREADER_HPP

// system includes
#include<vector>

// neopt core part
#include<system/types.h>
#include<system/IBinaryReader.h>
#include<numbers/nhelper.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class BinaryReader : public IBinaryReader
{
public:
   // read data directly on vector
   virtual void Read(vector<byte>& data, int begin, int readsize)
   {
   }

   virtual long ReadInt64()
   {
      return 0;
   }

   virtual vbyte ReadBytes(int max)
   {
      return vbyte(0);
   }

   // returns array of read bytes
   vbyte ReadVarBytes(int max = 0x1000000)
   {
       return this->ReadBytes((int)this->ReadVarInt((ulong)max));
   }

   template<class T>
   T ReadSerializable()
   {
      T obj; // empty constructor
      ISerializable& sobj = (ISerializable)obj;
      sobj.Deserialize(*this);
      return std::move(obj);
   }

   template<class T>
   vector<T> ReadSerializableArray(int max = 0x1000000)
   {
       vector<T> array(this->ReadVarInt((ulong)max));
       // invoking empty constructor for all of this kind
       for (int i = 0; i < array.size(); i++)
       {
          ISerializable& sobj = (ISerializable)array[i];
          sobj.Deserialize(*this);
       }
       return array;
   }

   ulong ReadVarInt()
   {
      return this->ReadVarInt(nhelper::MaxValue<ulong>());
   }

   ulong ReadVarInt(ulong max)
   {
       byte fb = this->ReadByte();
       ulong value;
       if (fb == 0xFD)
           value = this->ReadUInt16();
       else if (fb == 0xFE)
           value = this->ReadUInt32();
       else if (fb == 0xFF)
           value = this->ReadUInt64();
       else
           value = fb;
       if (value > max)
       {
          NEOPT_EXCEPTION("FormatException");
          return -1;
       }
       return value;
   }

   string ReadVarString(int max = 0x1000000)
   {
       return ""; // TODO // Encoding.UTF8.GetString(this->ReadVarBytes(max));
   }

};

}

#endif
