#ifndef HASH_SET_HPP
#define HASH_SET_HPP

// system includes
#include <iostream>
#include <unordered_set>
#include <vector>

// neopt core part
#include <system/types.h>
//#include<numbers/nhelper.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

template<class T>
class HashSet
{
private:
   struct baseT_hash
   {
      std::size_t operator()(const T& _node) const
      {
         return std::hash<std::string>()(_node.ToString());
      }
   };

private:
   std::unordered_set<T, baseT_hash> hashes;

public:
   HashSet()
   {
   }

   /*
   void Add(const T& obj)
   {
      hashes.emplace(obj);
   }
   */

   bool Add(T obj)
   {
      hashes.emplace(obj);
      return true;
   }
};

}

#endif
