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

   bool ContainsProperty(string key)
   {
      return mhelper::ContainsKey(properties, key);
   }

public:
   // TODO: implement as operator<<
   string ToString()
   {
      /*
         StringBuilder sb = new StringBuilder();
         sb.Append('{');
         foreach (KeyValuePair<string, JObject> pair in properties)
         {
             sb.Append('"');
             sb.Append(pair.Key);
             sb.Append('"');
             sb.Append(':');
             if (pair.Value == null)
             {
                 sb.Append("null");
             }
             else
             {
                 sb.Append(pair.Value);
             }
             sb.Append(',');
         }
         if (properties.Count == 0)
         {
             sb.Append('}');
         }
         else
         {
             sb[sb.Length - 1] = '}';
         }
         return sb.ToString();
         */
      return "";
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
