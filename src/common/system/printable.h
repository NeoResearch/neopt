#ifndef NEOPT_PRINTABLE_H
#define NEOPT_PRINTABLE_H

// Printable methods

// system
#include <iomanip> // fill zero for hex
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
//#include<decimal/decimal>

// neo core
#include "types.h"
#include "vhelper.hpp"

namespace neopt {

std::ostream&
operator<<(std::ostream& os, const vbyte& obj);

std::ostream&
operator<<(std::ostream& os, const vnibble& obj);

// how to print this?
//std::ostream& operator<<(std::ostream &os, const decimal::decimal64 &obj);

template<class T>
std::ostream&
operator<<(std::ostream& os, const std::vector<T>& obj);

}

#endif
