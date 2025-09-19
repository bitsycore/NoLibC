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

	const u8 s2[] = u8"123456789";
	const u64 len = strlen(s2);
	exit(strlenK(s2) + len);

	return 0;
}