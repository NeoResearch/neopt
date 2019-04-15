// Welcome to neopt project
// this main.cpp file should be deleted as soon as basic testing is fully configured on project
// for the final version, the "main" will in fact become some CLI tool (just like neo-cli),
//    that executes commands compatible to neo-cli standard
// now, this main is just for simple testing

// system includes
#include<iostream>
#include<vector>

// neopt core includes
#include<system/IEquatable.h>
#include<numbers/UIntBase.hpp>
#include<numbers/UInt160.hpp>
#include<IScriptContainer.h>
#include<IVerifiable.h>

using namespace std;
using namespace neopt;

int main()
{
   IEquatable<int>* ieq = nullptr;
   UIntBase* uint = nullptr;
   UInt160 uint160;
   IScriptContainer* iscript = nullptr;
   IVerifiable* iverifiable = nullptr;

   return 0;
}
