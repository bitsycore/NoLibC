#ifndef NOLIBC__SYSTEM_H
#define NOLIBC__SYSTEM_H

#include "../public/nlc_types.h"

extern volatile uSize gArgc;
extern volatile cStr* gArgv;
extern volatile cStr* gEnvp;
extern volatile uPtr* gAuxv;

#endif //NOLIBC__SYSTEM_H
