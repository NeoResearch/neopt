#ifndef VHELPER_HPP
#define VHELPER_HPP

// Vector Helper: vhelper

// system
#include<vector>
#include<algorithm>
#include<sstream>
#include<iomanip> // fill zero for hex

// neo core
#include<system/types.h>
#include<system/printable.h>
#include<system/ISerializable.h>
#include<system/IBinaryReader.h>
#include<system/BinaryReader.hpp>

using namespace std; // TODO: avoid!

namespace neopt
{

// vector helper class
class vhelper
{
public:

   template<class T>
   static vector<T> Reverse(const vector<T>& v)
   {
      vector<T> rev(v);
      std::reverse(rev.begin(), rev.end());
      return std::move(rev);
   }

   // TODO: replace by operator<< ?
   template<class T>
   static string ToHexString(const vector<T>& v)
   {
      stringstream ss;
      // TODO: check if format is this
      for(unsigned i=0; i<v.size(); i++) // TODO: use foreach
         ss << v[i];
      return ss.str();
   }

   static int GetVarSize(const vbyte& v)
   {
      // TODO: implement
      NEOPT_EXCEPTION("Not implemented GetVarSize");
      return 0;
   }

   static vbyte Skip(const vbyte& v, int count)
   {
      NEOPT_EXCEPTION("Not implemented Skip");
      return vbyte();
   }

   struct membuf : std::streambuf
   {
      membuf(char* begin, char* end)
      {
        this->setg(begin, begin, end);
      }
   };

   template<class T>
   static T AsSerializable(const vbyte& value, int start = 0)
   {
      //std::cout << "vhelper::AsSerializable!" << std::endl;
      //using (MemoryStream ms = new MemoryStream(value, start, value.Length - start, false))
      //using (BinaryReader reader = new BinaryReader(ms, Encoding.UTF8))
      std::istream* in = vhelper::ToIStream(value, start);
      IBinaryReader* reader = new BinaryReader(in, ((int)value.size())-start);//this->GetNewReader(in);

      T obj = reader->ReadSerializable<T>();
      delete reader;
      return std::move(obj);
   }

   // Gets new independent reader from stream (must delete stream later)
   //virtual IBinaryReader* GetNewReader(std::istream* stream) const = 0;



   static std::istream* ToIStream(const vbyte& param, int start = 0)//const vbyte& param)
   {
      //std::cout << "creating buffer: param size=" << param.size() << std::endl;
      const byte* buffer1 = param.data();
      //byte* buffer2 = (byte*)malloc(param.size()*sizeof(unsigned char));
      //std::cout << "buffer2 byte: size=" << sizeof(buffer2) << std::endl;
      //std::cout << "buffer byte: size=" << sizeof(buffer1) << " sizeint:" << sizeof(int) << " sizebyte:" << sizeof(byte) << std::endl;
      char* buffer = (char*)buffer1;
      //std::cout << "created buffer: size=" << sizeof(buffer) << std::endl;
      //for(unsigned i=0; i<(sizeof(buffer)/4); i++)
      //    std::cout << i << " :{" << ((int)(buffer[i])) << "}" << std::endl;
      membuf* sbuf = new membuf(buffer+start, buffer + sizeof(buffer));
      //std::cout << "created membuf" << std::endl;
      std::istream* in = new std::istream(sbuf);
      //std::cout << "built istream: " << in << std::endl;
      //byte b;
      //(*in) >> b;
      //std::cout << "read one byte: " << int(b) << std::endl;
      return in;
   }

   static vbyte ToArray(const ostream& os)
   {
      // TODO: implement
      NEOPT_EXCEPTION("Not implemented vhelper::ToArray() ostream");
      return vbyte(0);
   }


};

}

#endif
