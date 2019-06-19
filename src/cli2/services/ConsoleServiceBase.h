#ifndef CONSOLE_SERVICE_BASE_H
#define CONSOLE_SERVICE_BASE_H

// system includes
#include<string>
#include<vector>
#include<iostream>
#include<sstream>

// internal includes
#include<khelper.h>

namespace neopt
{

using namespace std; // TODO: remove

class ConsoleServiceBase
{
protected:
   virtual string Depends()
   {
      return "";
   }

   virtual string Prompt()
   {
      return "service";
   }

public:
   virtual string getServiceName() = 0;

   virtual string getVersion() = 0;

protected:
   bool ShowPrompt;

public:
   ConsoleServiceBase()
   {
      ShowPrompt = true;
   }

protected:

   virtual bool OnCommand(const vector<string>& args)
   {
      string cmd = khelper::ToLower(args[0]);
      if(cmd == "")
         return true;
      else if(cmd == "clear")
      {
         //Console.Clear();
         // TODO: clear console
         return true;
      }
      else if(cmd == "exit")
         return false;
      else if(cmd == "version")
      {
         //Console.WriteLine(Assembly.GetEntryAssembly().GetName().Version);
         std::cout << "my version"  << std::endl;
         return true;
      }
      else
      {
         //Console.WriteLine("error: command not found " + args[0]);
         std::cout << "error: command not found " << cmd << std::endl;
         return true;
      }
   }

protected:
   virtual void OnStart(const vector<string>& args) = 0;

   virtual void OnStop() = 0;

private:

   static vector<string> ParseCommandLine(const string& line)
   {
      vector<string> outputArgs;
      // TODO: improve this with better syntax detection... only single spaces now
      istringstream iss(line);
      string s;
      while ( getline( iss, s, ' ' ) )
      {
         outputArgs.push_back(s);
      }
      return std::move(outputArgs);
   }

/*
  public static string ReadPassword(string prompt)
  {
      const string t = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
      StringBuilder sb = new StringBuilder();
      ConsoleKeyInfo key;
      Console.Write(prompt);
      Console.Write(": ");

      Console.ForegroundColor = ConsoleColor.Yellow;

      do
      {
          key = Console.ReadKey(true);
          if (t.IndexOf(key.KeyChar) != -1)
          {
              sb.Append(key.KeyChar);
              Console.Write('*');
          }
          else if (key.Key == ConsoleKey.Backspace && sb.Length > 0)
          {
              sb.Length--;
              Console.Write(key.KeyChar);
              Console.Write(' ');
              Console.Write(key.KeyChar);
          }
      } while (key.Key != ConsoleKey.Enter);

      Console.ForegroundColor = ConsoleColor.White;
      Console.WriteLine();
      return sb.ToString();
  }

  public static SecureString ReadSecureString(string prompt)
  {
      const string t = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
      SecureString securePwd = new SecureString();
      ConsoleKeyInfo key;
      Console.Write(prompt);
      Console.Write(": ");

      Console.ForegroundColor = ConsoleColor.Yellow;

      do
      {
          key = Console.ReadKey(true);
          if (t.IndexOf(key.KeyChar) != -1)
          {
              securePwd.AppendChar(key.KeyChar);
              Console.Write('*');
          }
          else if (key.Key == ConsoleKey.Backspace && securePwd.Length > 0)
          {
              securePwd.RemoveAt(securePwd.Length - 1);
              Console.Write(key.KeyChar);
              Console.Write(' ');
              Console.Write(key.KeyChar);
          }
      } while (key.Key != ConsoleKey.Enter);

      Console.ForegroundColor = ConsoleColor.White;
      Console.WriteLine();
      securePwd.MakeReadOnly();
      return securePwd;
  }

 */
public:
  virtual void Run(const vector<string>& args)
  {
      OnStart(args);
      RunConsole();
      OnStop();
  }

private:

  void RunConsole()
  {
      bool running = true;
      vector<string> emptyarg;

      std::cout << getServiceName() << " Version: " << getVersion() << std::endl;
      std::cout << std::endl;

      while (running)
      {
          if (ShowPrompt)
          {
             // TODO: add some coloring here ;)
             std::cout << Prompt() << "> ";
          }

          std::string line;
          getline(cin, line);
          khelper::trim(line);
          if (line == "")
            continue;
          //break;

          vector<string> args = ParseCommandLine(line);

          running = OnCommand(args);
      }
  }

}; // class

} // namespace neopt

#endif
