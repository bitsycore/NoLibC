#ifndef NOLIBC__SYSTEM_H
#define NOLIBC__SYSTEM_H

#include "nlc_types.h"

extern volatile uSize gArgc;
extern volatile s8** gArgv;
extern volatile s8** gEnvp;
extern volatile uPtr* gAuxv;

#endif //NOLIBC__SYSTEM_H
