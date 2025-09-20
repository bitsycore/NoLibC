#include "private/syscall.h"

void Exit(const s64 status) {
	SysExit(status);
}