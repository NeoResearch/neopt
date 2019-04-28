#ifndef PRINTABLE_H
#define PRINTABLE_H

// Printable methods

// system
#include<vector>
#include<iostream>
#include<sstream>
#include<iomanip> // fill zero for hex
#include<ostream>
#include<decimal/decimal>

// neo core
#include<system/types.h>
#include<system/vhelper.hpp>

namespace neopt
{

std::ostream& operator<<(std::ostream &os, const vbyte &obj);

// how to print this?
//std::ostream& operator<<(std::ostream &os, const decimal::decimal64 &obj);

template<class T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &obj);

}

#endif
