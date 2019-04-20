#ifndef PRINTABLE_H
#define PRINTABLE_H

// Printable methods

// system
#include<vector>
#include<iostream>
#include<sstream>
#include<iomanip> // fill zero for hex
#include<ostream>

// neo core
#include<system/types.h>

namespace neopt
{

std::ostream& operator<<(std::ostream &os, const vbyte &obj);

template<class T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &obj);

}

#endif
