#ifndef IOBJECT_H
#define IOBJECT_H

// system includes
#include <vector>

// if possible, this class should be removed in the future. TODO

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class IObject
{
public:
   // TODO: what's needed here?

   virtual int GetHashCode() = 0;

   template<class T>
   static int ToInt32(vector<T>& v, int from = 0)
   {
      return 0;
   }
};

}

#endif
