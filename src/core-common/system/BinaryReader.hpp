#ifndef BINARYREADER_HPP
#define BINARYREADER_HPP

// system includes
#include <assert.h>
#include <fstream>
#include <iostream>
#include <vector>

// neopt core part
#include <numbers/nhelper.h>
#include <system/IBinaryReader.h>
#include <system/types.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

// this BinaryReader is not meant to be fully portable
// if necessary, think on a better portability class and re-write over IBinaryReader interface
class BinaryReader : public IBinaryReader
{
private:
   struct wrap_vector_as_istream : std::streambuf
   {
      wrap_vector_as_istream(std::vector<char>& v)
      {
         this->setg(&v[0], &v[0], &v[0] + v.size());
      }
   };

private:
   istream* input;
   bool mustDelete;
   int byteCount; // byte count must be precise here (or -1, meaning no limits)
   wrap_vector_as_istream* databuf;

public:
   // reading data from input stream
   // may not be fully portable
   // if necessary, in the future, create abstract Stream class with better cross-compatibility
   BinaryReader(istream& _input, int _byteCount = -1)
     : input(&_input)
     , mustDelete(false)
     , byteCount(_byteCount)
   {
      // ifstream reference would fit here (reading files)
      //std::cout << "BinaryReader::byteCountA = " << byteCount << std::endl;
      // -1 means no limit is known
      assert(byteCount >= -1);
      databuf = nullptr;
   }

   BinaryReader(istream* _input, int _byteCount = -1)
     : input(_input)
     , mustDelete(true)
     , byteCount(_byteCount)
   {
      //std::cout << "BinaryReader::byteCountB = " << byteCount << std::endl;
      // -1 means no limit is known
      assert(byteCount >= -1);
      databuf = nullptr;
   }
   /*
   struct membufx : std::streambuf
   {
      //membufx(char* begin, char* end)
      membufx(char* begin, char* end)
      {
         std::cout << "begin= " << (void*)begin << " end=" << (void*)end << std::endl;
         this->setg(begin, begin, end);
      }
   };
*/
   /*
   template<typename CharT, typename TraitsT = std::char_traits<CharT> >
   class vectorwrapbuf : public std::basic_streambuf<CharT, TraitsT> {
   public:
       vectorwrapbuf(std::vector<CharT> &vec) {
           this->setg(vec.data(), vec.data(), vec.data() + vec.size());
       }
   };
*/

   explicit BinaryReader(vbyte& bytes)
     : mustDelete(true)
     , byteCount(bytes.size())
   {
      //std::cout << "BinaryReader::byteCountC = " << byteCount << std::endl;
      //char* buffer = (char*)bytes.data();
      /*
      byte* buffer = bytes.data();
      if(sizeof(buffer) != bytes.size())
      {
         std::cout << "building BinaryReader with " << bytes.size() << " bytes!" << std::endl;
         std::cout << "buffer has size of " << sizeof(buffer) << " bytes!" << std::endl;
         for(unsigned i=0; i<bytes.size(); i++)
         {
            std::cout << "{i=" << i << " " << (uint)buffer[i] << "} ";
         }
         std::cout << std::endl;
      }
      */
      //membufx* sbuf = new membufx(bytes.begin(), bytes.end());//(char*)buffer, ((char*)buffer) + bytes.size()); /*sizeof(buffer)*/ // perhaps need to store this one too, to delete later
      //vectorwrapbuf<byte>* databuf = new vectorwrapbuf<byte>(bytes);
      vector<char>& sdata = (vector<char>&)(bytes);
      databuf = new wrap_vector_as_istream(sdata);
      input = new std::istream(databuf);
      //input = new std::istream(sbuf);
   }

   virtual ~BinaryReader()
   {
      if (mustDelete)
         delete input;
      if (databuf)
         delete databuf;
   }

   virtual int AvailableBytes() const
   {
      return byteCount;
   }

   virtual bool Good() const
   {
      return input->good();
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
      assert(byteCount != 0);
      assert((*input).good());

      //byte b = input->get();
      char b1;
      input->read(&b1, 1);
      byte b = (byte)b1;

      std::cout << "GCOUNT: " << input->gcount() << std::endl;
      if(!input->good())
      {
         std::cout << "WAS GOOD, NOT GOOD NOW!" << std::endl;
         std::cout << "eof: " << input->eof() << std::endl;
         std::cout << "bad: " << input->bad() << std::endl;
         std::cout << "fail: " << input->fail() << std::endl;
      }
      ////input->read(&b, 1);
      if(byteCount > 0)
         byteCount--;
      return b;
   }
   */

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

      //byte b = input->get();
      char b1;
      input->read(&b1, 1);
      byte b = (byte)b1;

      //std::cout << "GCOUNT: " << input->gcount() << std::endl;
      /*
      if(!input->good())
      {
         std::cout << "WAS GOOD, NOT GOOD NOW! b=" << (int) b << std::endl;
         std::cout << "eof: " << input->eof() << std::endl;
         std::cout << "bad: " << input->bad() << std::endl;
         std::cout << "fail: " << input->fail() << std::endl;
      }
      */
      ////input->read(&b, 1);
      if (byteCount > 0)
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
