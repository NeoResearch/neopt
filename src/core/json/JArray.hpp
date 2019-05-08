#ifndef JARRAY_HPP
#define JARRAY_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include "JObject.hpp"
#include <numbers/UIntBase.hpp>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/ITextReader.h>
#include <system/StringReader.hpp>
#include <system/mhelper.h>
#include <system/shelper.h>

namespace neopt {

class JArray : public JObject
{
public:
   vector<JObject*> items;

public:

   /*
   virtual std::string getValue() const
   {
      return this->ToString();
   }
   */

   JArray()
   {
   }

   JArray(vector<JObject*> _items)
     : items(_items)
   {
   }

   // TODO: provide initializer_list ?
   /*
   JArray(IEnumerable<JObject> items)
   {
      this.items.AddRange(items);
   }
*/

   JObject& operator[](int index)
   {
      return *items[index];
   }

   const JObject& operator[](int index) const
   {
      return *items[index];
   }

   int Count()
   {
      return items.size();
   }

   bool IsReadOnly()
   {
      return false;
   }

   void Add(JObject* item)
   {
      items.push_back(item);
   }

   virtual std::string AsString()
   {
      std::stringstream ss;
      for (unsigned i = 0; i < items.size(); i++) {
         ss << items[i]->ToString();
         if ((int)i != ((int)items.size()) - 1)
            ss << ",";
      }
      // TODO: implement this lambda
      //return string.Join(",", items.Select(p => p?.AsString()));
      return ss.str();
   }

   void Clear()
   {
      // TODO: should destroy? I think so... otherwise call items.clear() directly
      items.clear();
   }

   // TODO:
   /*
   bool Contains(JObject* item)
   {
      return items.Contains(item);
   }


   void CopyTo(JObject[] array, int arrayIndex)
   {
      items.CopyTo(array, arrayIndex);
   }
*/

   /*
   int IndexOf(JObject item)
   {
      return items.IndexOf(item);
   }
*/

   void Insert(int index, JObject* item)
   {
      //items.Insert(index, item);
      items.insert(items.begin() + index, item);
   }

   //bool Remove(JObject item)
   //{
   //return items.Remove(item);
   //}

   void RemoveAt(int index)
   {
      //items.RemoveAt(index);
      items.erase(items.begin() + index);
   }

   virtual std::string ToString() const override
   {
      //StringBuilder sb = new StringBuilder();
      std::stringstream sb;
      //sb.Append('[');
      sb << '[';
      //foreach (JObject item in items)
      for (unsigned i = 0; i < items.size(); i++) {
         JObject* item = items[i];
         if (item == nullptr)
            sb << "null";
         else
            sb << item->ToString();
         if ((int)i != ((int)items.size()) - 1)
            sb << ',';
      }
      sb << ']';
      return sb.str();
   }
};
}

#endif
