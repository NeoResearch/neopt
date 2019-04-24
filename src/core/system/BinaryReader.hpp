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
   int byteCount; // byte count must be precise here (or -1, meaning no limits)
public:

   // reading data from input stream
   // may not be fully portable
   // if necessary, in the future, create abstract Stream class with better cross-compatibility
   BinaryReader(istream& _input, int _byteCount = -1) :
      input(&_input), mustDelete(false), byteCount(_byteCount)
   {
      // ifstream reference would fit here (reading files)
      //std::cout << "BinaryReader::byteCountA = " << byteCount << std::endl;
      // -1 means no limit is known
      assert(byteCount >= -1);
   }

   BinaryReader(istream* _input, int _byteCount = -1) :
      input(_input), mustDelete(true), byteCount(_byteCount)
   {
      //std::cout << "BinaryReader::byteCountB = " << byteCount << std::endl;
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

   explicit BinaryReader(vbyte& bytes) :
      mustDelete(true), byteCount(bytes.size())
   {
      //std::cout << "BinaryReader::byteCountC = " << byteCount << std::endl;
      char* buffer = (char*)bytes.data();
      membufx* sbuf = new membufx(buffer, buffer + sizeof(buffer)); // perhaps need to store this one too, to delete later
      input = new std::istream(sbuf);
   }

   virtual ~BinaryReader()
   {
      if(mustDelete)
         delete input;
   }

   virtual int AvailableBytes() const
   {
      return byteCount;
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


   // native function
   /*
   virtual vbyte ReadBytes(int max)
   {
      vbyte bytes(max, 0);
      for(int i=0; i<max; i++)
      {
         bytes[i] = ReadByte();
         //(*input) >> bytes[i];
         //if(byteCount > 0)
         //   byteCount--;
         //std::cout << "byte " << i << "/" << max << ": " << (int)bytes[i] << std::endl;
      }
      return bytes;
      //NEOPT_EXCEPTION("BinaryReader::not implemented! readbytes");
      //return vbyte(0);
   }
   */

   // pack

   virtual byte ReadByte()
   {
      assert(byteCount != 0);
      assert((*input).good());
      byte b = input->get();
      ////input->read(&b, 1);
      if(byteCount > 0)
         byteCount--;
      return b;
   }

   string ReadVarString(int max = 0x1000000)
   {
      NEOPT_EXCEPTION("BinaryReader::not implemented! varstring");
       return ""; // TODO // Encoding.UTF8.GetString(this->ReadVarBytes(max));
   }
};

}

#endif
