#ifndef IBINARYREADER_H
#define IBINARYREADER_H

// system includes
#include<vector>
#include<iostream>
#include<fstream>

// neopt core part
#include<system/types.h>
#include<system/ISerializable.h> // TODO: move serialization to vhelper
#include<numbers/nhelper.h>
//#include<system/vhelper.hpp>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IBinaryReader
{
public:
   // read data directly on vector
   virtual void Read(vector<byte>& data, int begin, int readsize) = 0;

   // native function
   virtual vbyte ReadBytes(int max) = 0;

   // pack

   virtual byte ReadByte() = 0;

   virtual int16 ReadInt16() = 0;

   virtual uint16 ReadUInt16() = 0;

   virtual int32 ReadInt32() = 0;

   virtual uint32 ReadUInt32() = 0;

   virtual long ReadInt64() = 0;

   virtual ulong ReadUInt64() = 0;

   // returns array of read bytes
   virtual vbyte ReadVarBytes(int max = 0x1000000)
   {
       return this->ReadBytes((int)this->ReadVarInt((ulong)max));
   }


   template<class T>
   T ReadSerializable()
   {
      T obj; // empty constructor
      ISerializable& sobj = (ISerializable&)obj;
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

   virtual ulong ReadVarInt()
   {
      return this->ReadVarInt(nhelper::MaxValue<ulong>());
   }

   virtual ulong ReadVarInt(ulong max)
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

   virtual string ReadVarString(int max = 0x1000000) = 0;
};

}

#endif
