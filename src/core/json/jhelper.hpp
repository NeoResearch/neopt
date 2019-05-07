#ifndef JHELPER_HPP
#define JHELPER_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include "JObject.hpp"
#include "JString.hpp"
#include "JNumber.hpp"
#include "JBoolean.hpp"
#include "JArray.hpp"
#include <numbers/UIntBase.hpp>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/ITextReader.h>
#include <system/StringReader.hpp>
#include <system/mhelper.h>
#include <system/shelper.h>

// JSON Helper Class

namespace neopt {

class jhelper
{
public:
   static JObject* Parse(ITextReader& reader, int max_nest = 100)
   {
      if (max_nest < 0)
         NEOPT_EXCEPTION("JObject Parse FormatException");

      SkipSpace(reader);
      char firstChar = (char)reader.Peek();
      if (firstChar == '\"' || firstChar == '\'') {
         return ParseString(reader);
      }
      if (firstChar == '[') {
         return ParseArray(reader, max_nest);
      }
      if ((firstChar >= '0' && firstChar <= '9') || firstChar == '-') {
         return ParseNumber(reader);
      }
      if (firstChar == 't' || firstChar == 'f') {
         return ParseBoolean(reader);
      }
      if (firstChar == 'n') {
         return ParseNull(reader);
      }
      if (reader.Read() != '{')
         NEOPT_EXCEPTION("JObject Parse FormatException");
      SkipSpace(reader);
      JObject* obj = new JObject();
      while (reader.Peek() != '}') {
         if (reader.Peek() == ',')
            reader.Read();
         SkipSpace(reader);
         string name = ParseString(reader)->getValue();
         SkipSpace(reader);
         if (reader.Read() != ':')
            NEOPT_EXCEPTION("JObject Parse FormatException");
         JObject* value = Parse(reader, max_nest - 1);
         obj->properties.Add(name, value);
         SkipSpace(reader);
      }
      reader.Read(); // consume what?
      return obj;
   }

   static JObject* Parse(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return Parse(reader, max_nest);
   }

private:
   static JObject* ParseNull(ITextReader& reader)
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

private: // TODO test
   static void SkipSpace(ITextReader& reader)
   {
      while (reader.Peek() == ' ' || reader.Peek() == '\t' || reader.Peek() == '\r' || reader.Peek() == '\n') {
         reader.Read();
      }
   }

public:
   static JString* ParseString(ITextReader& reader, int max_nest = 100)
   {
      return nullptr;
   }

   static JString* ParseString(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseString(reader, max_nest);
   }

   static JNumber* ParseNumber(ITextReader& reader, int max_nest = 100)
   {
      return nullptr;
   }

   static JNumber* ParseNumber(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseNumber(reader, max_nest);
   }

   static JBoolean* ParseBoolean(ITextReader& reader, int max_nest = 100)
   {
      return nullptr;
   }

   static JBoolean* ParseBoolean(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseBoolean(reader, max_nest);
   }

   static JArray* ParseArray(ITextReader& reader, int max_nest = 100)
   {
      return nullptr;
   }

   static JArray* ParseArray(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseArray(reader, max_nest);
   }
};
}

#endif
