#ifndef BINARYREADER_HPP
#define BINARYREADER_HPP

// system includes
#include<vector>
#include<iostream>
#include<fstream>
#include<assert.h>

// neopt core part
#include<system/types.h>
#include<system/IBinaryReader.h>
#include<numbers/nhelper.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

// this BinaryReader is not meant to be fully portable
// if necessary, think on a better portability class and re-write over IBinaryReader interface
class BinaryReader : public IBinaryReader
{
private:
   istream* input;
   bool mustDelete;
   int byteCount; // byte count must be precise here
public:

   // reading data from input stream
   // may not be fully portable
   // if necessary, in the future, create abstract Stream class with better cross-compatibility
   BinaryReader(istream& _input, int _byteCount = -1) :
      input(&_input), mustDelete(false), byteCount(_byteCount)
   {
      // -1 means no limit is known
      assert(byteCount >= -1);
   }

   BinaryReader(istream* _input, int _byteCount = -1) :
      input(_input), mustDelete(true), byteCount(_byteCount)
   {
      // -1 means no limit is known
      assert(byteCount >= -1);
   }

   struct membufx : std::streambuf
   {
      membufx(char* begin, char* end)
      {
        this->setg(begin, begin, end);
      }
   };

   BinaryReader(vbyte& bytes) :
      mustDelete(true), byteCount(bytes.size())
   {
      char* buffer = (char*)bytes.data();
      membufx* sbuf = new membufx(buffer, buffer + sizeof(buffer)); // perhaps need to store this one too, to delete later
      input = new std::istream(sbuf);
   }

   virtual ~BinaryReader()
   {
      if(mustDelete)
         delete input;
   }

/*
   // Gets new independent reader from stream (must delete stream later)
   virtual IBinaryReader* GetNewReader(std::istream* stream) const
   {
      return new BinaryReader(stream);
   }
*/

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
      assert(byteCount != 0);
      byte b;
      (*input) >> b;
      if(byteCount > 0)
         byteCount--;
      return b;
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
};

}

#endif
