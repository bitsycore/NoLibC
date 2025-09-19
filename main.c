#include "nolibc/nolibc.h"

int main() {
	const u8 s[] = u8"Test123";

	print(s);
	printNewLine();
	print2(s, strlenK(s));
	printNewLine();
	printK(s);
	printNewLine();

	println(s);
	println2(s, strlenK(s));
	printlnK(s);

	printlnF(u8"Hello %s I am here %s", s, s);
	printlnF(u8"Test %d, 0x%x", 55, 0x66);

	const u8 s2[] = u8"123456789";
	const u64 len = strlen(s2);

	printlnF(u8"strlen: %d", len);
	printlnF(u8"strlenK: %d", strlenK(s2));

	printF(u8"Hello\nTest");

	return 0;
}