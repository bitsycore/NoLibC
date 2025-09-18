#include "nolibc/nolibc.h"

int main() {
	puts(u8"hello, world");
	putsEx(u8"hello, world (putsEx)");
	putcLr();
	exit(strlen(u8"123456789"));
	return 0;
}