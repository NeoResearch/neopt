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
   // note that parameter is const, since it's not supposed to update them...
   // it's useful for on-time compute functions, such as getHash(), which are not harmful to the base class, but const_cast can be used when sure of that
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

   // pointer version
   template<class T1, class T2>
   static vector<T2> SelectP(const vector<T1*>& v1, std::function<T2(const T1*)> sel)
   {
      vector<T2> ret(v1.size());
      std::transform(v1.begin(),
                   v1.end(),
                   ret.begin(),
                   [&sel](const T1* a) -> T2 { return sel(a); });
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
      if(count < v.size())
      {
        vbyte p(v.begin()+count, v.end());
        return std::move(p);
      }
      else
        return std::move(vbyte(0));
   }

/*
   struct membuf : std::streambuf
   {
      membuf(char* begin, char* end)
      {
        this->setg(begin, begin, end);
      }
   };
*/

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

};

}

#endif
