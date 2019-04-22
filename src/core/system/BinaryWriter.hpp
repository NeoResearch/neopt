#ifndef BINARY_WRITER_HPP
#define BINARY_WRITER_HPP

// system includes
#include<vector>
#include<iostream>
#include<fstream>

// neopt core part
#include<system/types.h>
#include<system/IBinaryWriter.h>
//#include<numbers/nhelper.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

// this BinaryReader is not meant to be fully portable
// if necessary, think on a better portability class and re-write over IBinaryReader interface
class BinaryWriter : public IBinaryWriter
{
private:
   ostream* output;
   bool mustDelete;
public:

   // writing data on output stream
   // may not be fully portable
   // if necessary, in the future, create abstract Stream class with better cross-compatibility
   BinaryWriter(ostream& _output) :
      output(&_output), mustDelete(false)
   {
   }

   BinaryWriter(ostream* _output) :
      output(_output), mustDelete(true)
   {
   }

   virtual ~BinaryWriter()
   {
      if(mustDelete)
         delete output;
   }


   // writes data directly from vector
   virtual void Write(const vector<byte>& data)
   {
   }

   virtual void Write(long v)
   {
   }

   // writes var bytes on vector
   virtual void WriteVarBytes(vbyte& v)
   {
   }

   virtual void Flush()
   {
      output->flush(); // don't know if actually needed
   }

/*
   // Gets new independent reader from stream (must delete stream later)
   virtual IBinaryReader* GetNewReader(std::istream* stream) const
   {
      return new BinaryReader(stream);
   }
*/
/*

   static bool FileExists(std::string name)
   {
      std::ifstream f(name.c_str());
      return f.good();
   }

   // read data directly on vector
   void Read(vector<byte>& data, int begin, int readsize)
   {

   }

   // returns array of read bytes
   virtual vbyte ReadVarBytes(int max)
   {
      return vbyte(0);
   }

   // native function
   virtual vbyte ReadBytes(int max)
   {
      return vbyte(0);
   }

   // pack

   virtual byte ReadByte()
   {
      return 0;
   }

   virtual int16 ReadInt16()
   {
      return 0;
   }

   virtual uint16 ReadUInt16()
   {
      return 0;
   }

   virtual int32 ReadInt32()
   {
      return 0;
   }

   virtual uint32 ReadUInt32()
   {
      return 0;
   }

   virtual long ReadInt64()
   {
      return 0;
   }

   virtual ulong ReadUInt64()
   {
      return 0;
   }

   string ReadVarString(int max = 0x1000000)
   {
       return ""; // TODO // Encoding.UTF8.GetString(this->ReadVarBytes(max));
   }
   */
};

}

#endif
