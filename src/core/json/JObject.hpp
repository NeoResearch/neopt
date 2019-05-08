#ifndef JOBJECT_HPP
#define JOBJECT_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include <numbers/UIntBase.hpp>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/ITextReader.h>
#include <system/StringReader.hpp>
#include <system/mhelper.h>
#include <system/shelper.h>

namespace neopt {

class JObject
{
public:
   //static JObject Null() = null;
   //private:
public:
   map<string, JObject*> properties;

public:
   JObject& operator[](string name)
   {
      return *properties[name];
   }

   const map<string, JObject*> Properties()
   {
      return properties;
   }

   virtual bool AsBoolean()
   {
      return true;
   }

   virtual double AsNumber()
   {
      return NAN;
   }

   virtual string AsString()
   {
      return "[object Object]";
   }

   virtual std::string getValue() const
   {
      return this->ToString();
   }

   bool ContainsProperty(string key)
   {
      return mhelper::ContainsKey(properties, key);
   }

public:
   virtual std::string ToString() const
   {
      //StringBuilder sb = new StringBuilder();
      std::stringstream sb;
      //sb.Append('{');
      sb << '{';
      //foreach (KeyValuePair<string, JObject> pair in properties)
      for (auto pair = properties.begin(); pair != properties.end(); ++pair) {
         sb << '"';
         sb << pair->first;
         sb << '"';
         sb << ':';
         if (pair->second == nullptr) {
            sb << "null";
         } else {
            sb << pair->second->getValue();
         }
         sb << ',';
      }
      std::string sf = sb.str();
      if (properties.size() == 0) {
         sf.append("}");
      } else {
         sf[sf.size() - 1] = '}';
      }
      return sf;
   }

   /*
           public virtual T TryGetEnum<T>(T defaultValue = default, bool ignoreCase = false) where T : Enum
           {
               return defaultValue;
           }

           public static implicit operator JObject(Enum value)
           {
               return new JString(value.ToString());
           }

           public static implicit operator JObject(JObject[] value)
           {
               return new JArray(value);
           }

           public static implicit operator JObject(bool value)
           {
               return new JBoolean(value);
           }

           public static implicit operator JObject(double value)
           {
               return new JNumber(value);
           }

           public static implicit operator JObject(string value)
           {
               return value == null ? null : new JString(value);
          }
          */
public:
   JObject& operator=(const string value)
   {
      NEOPT_EXCEPTION("Not implemented: operator= JObject string")
      return *this;
   }
};
}

#endif
