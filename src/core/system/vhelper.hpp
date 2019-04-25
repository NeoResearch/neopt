#ifndef VHELPER_HPP
#define VHELPER_HPP

// Vector Helper: vhelper

// system
#include<vector>
#include<algorithm>
#include<sstream>
#include<iomanip> // fill zero for hex
#include<functional>

// neo core
#include<system/types.h>
//#include<system/printable.h>
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

   // Concat copy
   template<class T>
   static vector<T> Concat(const vector<T>& v1, const vector<T>& v2) // will return copy
   {
      vector<T> v(v1);
      v.insert(v.end(), v2.begin(), v2.end());
      return std::move(v);
   }

/*
   template<class T>
   static void Concat(vector<T>& v1, vector<T>& v2) // will empty v2 and put after v1
   {
      v1.insert(v1.begin(), v2.begin(), v2.end());
      v2.clear();
   }
*/

   // TODO: replace by operator<< ?
   /*
   template<class T>
   static string ToHexString(const vector<T>& v)
   {
      stringstream ss;
      // TODO: check if format is this
      for(unsigned i=0; i<v.size(); i++) // TODO: use foreach
         ss << v[i];
      return ss.str();
   }
   */

   // 'where' using erase-remove-idiom
   template<class T>
   static vector<T> Where(const vector<T>& v1, std::function<bool(const T&)> sel)
   {
      vector<T> v(v1);
      v.erase(std::remove_if(v.begin(),
                                v.end(),
                                [&sel](const T& val){return !sel(val);}
                             ), v.end());
      return std::move(v);
   }

   // 'select' using transform pattern
   template<class T1, class T2>
   static vector<T2> Select(const vector<T1>& v1, std::function<T2(const T1&)> sel)
   {
      vector<T2> ret(v1.size());
      std::transform(v1.begin(),
                   v1.end(),
                   ret.begin(),
                   [&sel](const T1& a) -> T2 { return sel(a); });
      return std::move(ret);
   }


   static string ToHexString(const vbyte& v)
   {
      //std::cout << "ToHexString!!!!" << std::endl;
      stringstream ss;
      // TODO: check if format is this
      for(unsigned i=0; i<v.size(); i++) // TODO: use foreach
         ss << std::setfill('0') << std::setw(2) << std::hex << (int)v[i];
      //std::cout << "ToHexString!!!! RESULT = " << ss.str() << std::endl;

      return ss.str();
   }

   static string ToHexString(const byte& b)
   {
      return ToHexString(vbyte(1,b));
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
      //std::istream* in = vhelper::ToIStream(value, start);
      vbyte part(value.begin()+start, value.end());
      BinaryReader reader(part); //new BinaryReader(in, ((int)value.size())-start);//this->GetNewReader(in);

      T obj = reader.ReadSerializable<T>();
      //delete reader;
      return std::move(obj);
   }

   // Gets new independent reader from stream (must delete stream later)
   //virtual IBinaryReader* GetNewReader(std::istream* stream) const = 0;


/*
   static std::istream* ToIStream(const vbyte& param, int start = 0)//const vbyte& param)
   {
      std::cout << "DEPRECATING ToIStream ????? " << std::endl;
      std::cout << "Please try not to use ToIStream ????? " << std::endl;

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
*/

/*
   static vbyte ToArray(const ostream& os)
   {
      // TODO: implement
      NEOPT_EXCEPTION("Not implemented vhelper::ToArray() ostream");
      return vbyte(0);
   }
*/


   template<class T>
   static T DeserializeFrom(const vbyte& value, int offset = 0)
   {
      if(offset >= value.size())
         NEOPT_EXCEPTION("vhelper::DeserializeFrom: OFFSET BIGGER THAN AVAILABLE BYTES!");

      vbyte data(value.begin()+offset, value.begin()+value.size()-offset);
      BinaryReader reader(data);
      // using (MemoryStream ms = new MemoryStream(value, offset, value.Length - offset, false))
      // using (BinaryReader reader = new BinaryReader(ms, Encoding.UTF8))
      T obj;
      obj.DeserializeFrom(reader);
      return std::move(obj);
   }


};

}

#endif
