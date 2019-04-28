#include<system/printable.h>

using namespace std;

ostream& neopt::operator<<(ostream &os, const vbyte &obj)
{
   stringstream ss; // do not dirty 'os' with specific formatting
	ss << "[" << obj.size() << "]0x";
	if (obj.size() > 0)
      ss << vhelper::ToHexString(obj);
		//for (unsigned int i = 0; i < obj.size(); i++)
		//	ss << std::setfill('0') << std::setw(2) << std::hex << (int)obj[i];
	return os << ss.str();
}

// how to print this?
/*
ostream& operator<<(ostream &os, const decimal::decimal64& obj)
{
   stringstream ss;
	ss << ((long)obj);
	return os << ss.str();
}
*/

template<class T>
ostream& neopt::operator<<(ostream &os, const vector<T>& obj)
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
