#ifndef TYPES_H
#define TYPES_H

namespace neopt
{
// basic types for Neo core

// the simplest chunk of information
typedef unsigned char byte;

#define NEOPT_EXCEPTION(str) { printf("neopt error: %s\n", str); exit(1); }

}

#endif
