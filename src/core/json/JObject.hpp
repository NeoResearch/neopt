#ifndef JOBJECT_HPP
#define JOBJECT_HPP

// c++ standard part
#include<vector>
#include<map>
#include<cmath> // NAN

// neopt core part
#include<system/ISerializable.h>
#include<system/IEquatable.h>
#include<system/IComparable.h>
#include<numbers/UIntBase.hpp>
#include<system/shelper.h>
#include<system/mhelper.h>
#include<system/ITextReader.h>

namespace neopt
{

   class JObject
   {
   public:
      //static JObject Null() = null;
   private:
      map<string, JObject> properties;

   public:
      JObject& operator[](string name)
      {
         return properties[name];
      }

      const map<string, JObject> Properties()
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

      static JObject Parse(ITextReader& reader, int max_nest = 100)
      {
         if (max_nest < 0)
            NEOPT_EXCEPTION("FormatException");
         //throw new FormatException();
         /*
         SkipSpace(reader);
         char firstChar = (char)reader.Peek();
         if (firstChar == '\"' || firstChar == '\'')
         {
             return JString.Parse(reader);
         }
         if (firstChar == '[')
         {
             return JArray.Parse(reader, max_nest);
         }
         if ((firstChar >= '0' && firstChar <= '9') || firstChar == '-')
         {
             return JNumber.Parse(reader);
         }
         if (firstChar == 't' || firstChar == 'f')
         {
             return JBoolean.Parse(reader);
         }
         if (firstChar == 'n')
         {
             return ParseNull(reader);
         }
         if (reader.Read() != '{') throw new FormatException();
         SkipSpace(reader);
         JObject obj = new JObject();
         while (reader.Peek() != '}')
         {
             if (reader.Peek() == ',') reader.Read();
             SkipSpace(reader);
             string name = JString.Parse(reader).Value;
             SkipSpace(reader);
             if (reader.Read() != ':') throw new FormatException();
             JObject value = Parse(reader, max_nest - 1);
             obj.properties.Add(name, value);
             SkipSpace(reader);
         }
         reader.Read();
         return obj;
         */
         return JObject();
      }

      static JObject Parse(string value, int max_nest = 100)
      {
         /*
         using (StringReader reader = new StringReader(value))
         {
             return Parse(reader, max_nest);
         }
         */
         return JObject();
      }

   private:
      static JObject ParseNull(ITextReader& reader)
      {
         /*
         char firstChar = (char)reader.Read();
         if (firstChar == 'n')
         {
             int c2 = reader.Read();
             int c3 = reader.Read();
             int c4 = reader.Read();
             if (c2 == 'u' && c3 == 'l' && c4 == 'l')
             {
                 return null;
             }
         }
         throw new FormatException();
         */
         return JObject();
      }

   protected:

      static void SkipSpace(ITextReader& reader)
      {
         /*
         while (reader.Peek() == ' ' || reader.Peek() == '\t' || reader.Peek() == '\r' || reader.Peek() == '\n')
         {
             reader.Read();
         }
         */
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
