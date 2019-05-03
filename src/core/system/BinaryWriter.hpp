#ifndef BINARY_WRITER_HPP
#define BINARY_WRITER_HPP

// system includes
#include <fstream>
#include <iostream>
#include <vector>

// neopt core part
#include <system/IBinaryWriter.h>
#include <system/types.h>
//#include<numbers/nhelper.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

// this BinaryReader is not meant to be fully portable
// if necessary, think on a better portability class and re-write over IBinaryReader interface
class BinaryWriter : public IBinaryWriter
{
private:
   //ostream* output;
   //bool mustDelete;
   vbyte* data_bytes; // if available, write here
   bool delete_array;

public:
   // writing data on output stream
   // may not be fully portable
   // if necessary, in the future, create abstract Stream class with better cross-compatibility
   /*
   BinaryWriter(ostream& _output) :
      output(&_output), mustDelete(false), data_bytes(nullptr)
   {
   }

   BinaryWriter(ostream* _output) :
      output(_output), mustDelete(true), data_bytes(nullptr)
   {
   }

   BinaryWriter(vbyte& data) :
      output(nullptr), mustDelete(false), data_bytes(&data)
   {
   }
   */
   BinaryWriter(vbyte& data)
     : data_bytes(&data)
     , delete_array(false)
   {
   }

   BinaryWriter()
     : data_bytes(new vbyte())
     , delete_array(true)
   {
   }

   virtual ~BinaryWriter()
   {
      //if(mustDelete && output)
      //   delete output;
      if (delete_array)
         delete data_bytes;
      //output = nullptr;
      data_bytes = nullptr;
   }

   using IBinaryWriter::Write;

   virtual void Write(byte v)
   {
      if (data_bytes)
         data_bytes->push_back(v);
      else
         NEOPT_EXCEPTION("NOT IMPLEMENTED WITH OTHER BUFFER TYPE!");
   }

   virtual int CountBytes() const
   {
      if (data_bytes)
         return int(data_bytes->size());
      return -1; // unknown
   }

   //   virtual void Flush()
   //   {
   //output->flush(); // don't know if actually needed
   //   }

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
