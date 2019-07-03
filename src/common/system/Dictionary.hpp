#ifndef NEOPT_COMMON_SYSTEM_DICTIONARY_HPP
#define NEOPT_COMMON_SYSTEM_DICTIONARY_HPP

// system includes
#include <iostream>
#include <map>
#include <vector>

// neopt core part
#include <system/types.h>
//#include<numbers/nhelper.h>

using namespace std;

namespace neopt {

template<class Key, class Value>
class Dictionary
{
private:
   map<Key, Value> dictionary;

public:
   Value& operator[](const Key& key)
   {
      return dictionary[key];
   }

   int Count() const
   {
      return dictionary.size();
   }

   void Add(Key& key, Value& value)
   {
      dictionary[key] = value;
   }

   // TODO: avoid memory leaks
   void Clear()
   {
      dictionary.clear();
   }

   bool ContainsKey(const Key& key)
   {
      return dictionary->find(key) != dictionary.end();
   }

   bool Remove(const Key& key)
   {
      return dictionary.erase(key);
   }

   // if null, didn't find element. otherwise, pointer is returned
   Value* TryGetValue(const Key& key)
   {
      if (!ContainsKey(key))
         return nullptr;
      return &dictionary[key];
   }
};
}

#endif // NEOPT_COMMON_SYSTEM_DICTIONARY_HPP