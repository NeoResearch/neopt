#ifndef IBINARYREADER_H
#define IBINARYREADER_H

// system includes
#include<vector>
#include<iostream>
#include<fstream>

// neopt core part
#include<system/types.h>
#include<system/ISerializable.h>
//#include<numbers/nhelper.h>
//#include<system/vhelper.hpp>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IBinaryReader
{
public:

   // the most fundamental method to be implemented! how to get a single byte...
   virtual byte ReadByte() = 0;

   // return count of bytes available for reading (-1 is used if value is unknown)
   virtual int AvailableBytes() const
   {
      return -1; // -1 means 'unknown'
   }

   virtual bool Good() const
   {
      return true;
   }

   // read data directly on vector, of size 'readsize', at position 'begin' (used on UIntBase)
   virtual void Read(vector<byte>& data, int begin, int readsize)
   {
      // vector must have enough size
      if(begin+readsize > data.size())
      {
         NEOPT_EXCEPTION("IBinaryReader::Read error. Not enough space on array");
         return;
      }
      vbyte bytes = ReadBytes(readsize);
      for(int i=0; i<readsize; i++)
         data[begin+i] = bytes[i];
   }

   // default implementation function
   virtual vbyte ReadBytes(int max)
   {
      //std::cout << "ReadBytes: " << max << std::endl;
      if((AvailableBytes() != -1) && (AvailableBytes() < max))
         NEOPT_EXCEPTION("IBinaryReader::Cannot read enough bytes!"); // or, return vbyte(0); TODO
      vbyte bytes(max, 0);
      for(int i=0; i<bytes.size(); i++)
      {
         bytes[i] = ReadByte();
         //std::cout << "byte " << i << " : " << (int)bytes[i] << " good:" << Good() << std::endl;
      }
      return bytes;
   }

   // read int16 in little-endian format
   virtual int16 ReadInt16()
   {
      vbyte bytes = ReadBytes(2);
      int16 val = bytes[0] | (bytes[1]<<8);
      return val;
   }

   // read uint16 in little-endian format
   virtual uint16 ReadUInt16()
   {
      vbyte bytes = ReadBytes(2);
      uint16 val = bytes[0] | (bytes[1]<<8);
      return val;
   }

   // read int32 in little-endian format
   virtual int32 ReadInt32()
   {
      vbyte bytes = ReadBytes(4);
      int32 val = bytes[0] | (bytes[1]<<8) | (bytes[2]<<16) | (bytes[3]<<24);
      return val;
   }

   // read uint32 in little-endian format
   virtual uint32 ReadUInt32()
   {
      vbyte bytes = ReadBytes(4);
      uint32 val = bytes[0] | (bytes[1]<<8) | (bytes[2]<<16) | (bytes[3]<<24);
      return val;
   }

   // little-endian
   virtual long ReadInt64()
   {
      vbyte bytes = ReadBytes(8);
      uint32 val1 = bytes[0] | (bytes[1]<<8) | (bytes[2]<<16) | (bytes[3]<<24);
      long val2 = bytes[4] | (bytes[5]<<8) | (bytes[6]<<16) | (bytes[7]<<24);
      long val = val1 | val2 << 32;
      return val;
   }

   // little-endian
   virtual ulong ReadUInt64()
   {
      vbyte bytes = ReadBytes(8);
      uint32 val1 = bytes[0] | (bytes[1]<<8) | (bytes[2]<<16) | (bytes[3]<<24);
      ulong val2 = bytes[4] | (bytes[5]<<8) | (bytes[6]<<16) | (bytes[7]<<24);
      ulong val = val1 | val2 << 32;
      return val;
   }

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
      return this->ReadVarInt(types::MaxValue<ulong>());
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
