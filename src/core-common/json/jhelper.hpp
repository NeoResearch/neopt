#ifndef JHELPER_HPP
#define JHELPER_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include "JArray.hpp"
#include "JBoolean.hpp"
#include "JNumber.hpp"
#include "JObject.hpp"
#include "JString.hpp"
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
         NEOPT_EXCEPTION("JObject Parse (max_nest < 0) FormatException");

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
      char c1 = reader.Read();
      if (c1 != '{') {
         std::cout << "SHOULD NOT READ '" << c1 << "'" << std::endl;
         NEOPT_EXCEPTION("JObject Parse (read '{') FormatException");
      }
      SkipSpace(reader);
      JObject* obj = new JObject();
      while (reader.Peek() != '}') {
         if (reader.Peek() == ',')
            reader.Read();
         SkipSpace(reader);
         string name = ParseString(reader)->getValue();
         SkipSpace(reader);
         if (reader.Read() != ':')
            NEOPT_EXCEPTION("JObject Parse (read ':') FormatException");
         JObject* value = Parse(reader, max_nest - 1);
         obj->properties[name] = value; // .Add
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
      char firstChar = (char)reader.Read();
      if (firstChar == 'n') {
         int c2 = reader.Read();
         int c3 = reader.Read();
         int c4 = reader.Read();
         if (c2 == 'u' && c3 == 'l' && c4 == 'l') {
            return nullptr;
         }
      }
      NEOPT_EXCEPTION("ParseNull FormatException");
      return nullptr;
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
      SkipSpace(reader);
      char* buffer = new char[4];
      char firstChar = (char)reader.Read();
      if (firstChar != '\"' && firstChar != '\'')
         NEOPT_EXCEPTION("JString FormatException");
      //throw new FormatException();
      //StringBuilder sb = new StringBuilder();
      std::stringstream sb;
      while (true) {
         char c = (char)reader.Read();
         if (c == 65535)
            //throw new FormatException();
            NEOPT_EXCEPTION("JString 65535 FormatException");
         if (c == firstChar)
            break;
         if (c == '\\') {
            c = (char)reader.Read();
            switch (c) {
               case 'u': {
                  reader.Read(buffer, 0, 4); // read four chars to buffer
                  string sbuffer(buffer);
                  c = (char)shelper::ParseHexToShort(sbuffer); // TODO: test endianess (big or little?)
                  //c = (char)short.Parse(new string(buffer), NumberStyles.HexNumber); // TODO: verify if that's the same
                  break;
               }
               case 'r': {
                  c = '\r';
                  break;
               }
               case 'n': {
                  c = '\n';
                  break;
               }
            }
         }
         sb << c;
      }
      delete[] buffer;
      string sf = sb.str();
      return new JString(sf);
   }

   static JString* ParseString(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseString(reader, max_nest);
   }

   static JNumber* ParseNumber(ITextReader& reader, int max_nest = 100)
   {
      SkipSpace(reader);
      //StringBuilder sb = new StringBuilder();
      std::stringstream sb;
      while (true) {
         char c = (char)reader.Peek();
         if (c >= '0' && c <= '9' || c == '.' || c == '-') {
            sb << c;
            reader.Read();
         } else {
            break;
         }
      }
      std::string sf = sb.str();
      //return new JNumber(double.Parse(sf));
      return new JNumber(shelper::ParseDouble(sf));
   }

   static JNumber* ParseNumber(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseNumber(reader, max_nest);
   }

   static JBoolean* ParseBoolean(ITextReader& reader, int max_nest = 100)
   {
      SkipSpace(reader);
      char firstChar = (char)reader.Read();
      if (firstChar == 't') {
         int c2 = reader.Read();
         int c3 = reader.Read();
         int c4 = reader.Read();
         if (c2 == 'r' && c3 == 'u' && c4 == 'e') {
            return new JBoolean(true);
         }
      } else if (firstChar == 'f') {
         int c2 = reader.Read();
         int c3 = reader.Read();
         int c4 = reader.Read();
         int c5 = reader.Read();
         if (c2 == 'a' && c3 == 'l' && c4 == 's' && c5 == 'e') {
            return new JBoolean(false);
         }
      }
      NEOPT_EXCEPTION("JBoolean Parse FormatException");
      //throw new FormatException();
      return nullptr;
   }

   static JBoolean* ParseBoolean(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseBoolean(reader, max_nest);
   }

   static JArray* ParseArray(ITextReader& reader, int max_nest = 100)
   {
      if (max_nest < 0)
         NEOPT_EXCEPTION("JArray FormatException");
      SkipSpace(reader);
      if (reader.Read() != '[')
         NEOPT_EXCEPTION("JArray FormatException");
      SkipSpace(reader);
      JArray* array = new JArray();
      while (reader.Peek() != ']') {
         if (reader.Peek() == ',')
            reader.Read();
         JObject* obj = Parse(reader, max_nest - 1);
         //array->items.Add(obj);
         array->items.push_back(obj);
         SkipSpace(reader);
      }
      reader.Read();
      return array;
   }

   static JArray* ParseArray(string value, int max_nest = 100)
   {
      StringReader reader(value);
      return ParseArray(reader, max_nest);
   }
};
}

#endif
