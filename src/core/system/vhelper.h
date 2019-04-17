#ifndef VHELPER_H
#define VHELPER_H

// Vector Helper: vhelper

// system
#include<vector>
#include<algorithm>
#include<sstream>

// neo core
#include<system/types.h>

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
};

ostream& operator<<(ostream &os, const vbyte &obj)
{
	os << "0x";
	if (obj.size() > 0)
		for (unsigned int i = 0; i < obj.size(); i++)
			os << std::hex << (int)obj[i];
	return os;
}


template<class T>
ostream& operator<<(ostream &os, const vector<T> &obj)
{
	os << "vector(" << obj.size() << ") [";

	if (obj.size() > 0)
	{
		for (unsigned int i = 0; i < obj.size() - 1; i++)
			os << obj.at(i) << " , ";
		os << obj.at(obj.size() - 1);
	}

	os << "]";

	return os;
}

// TODO: define all operators here that are necessary

}

#endif
