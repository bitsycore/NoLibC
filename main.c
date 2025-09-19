#include "nolibc.h"

int main() {

	// --------------------------------------

	print("[TEST]: print\n");
	printLen("[TEST]: printLen\n", strlenK("[TEST]: printLen\n"));
	printK("[TEST]: printK\n");

	// --------------------------------------

	printFile(FILE_STDOUT, "[TEST]: printFile\n");
	printFileLen(FILE_STDOUT, "[TEST]: printFileLen\n", strlenK("[TEST]: printFileLen\n"));
	printFileK(FILE_STDOUT, "[TEST]: printFileK\n");

	// --------------------------------------

	printLn("[TEST]: printLn");
	printLnLen("[TEST]: printLnLen", strlenK("[TEST]: printLnLen"));
	printLnK("[TEST]: printLnK");

	// --------------------------------------

	printLnFile(FILE_STDOUT, "[TEST]: printLnFile");
	printLnFileLen(FILE_STDOUT, "[TEST]: printLnFileLen", strlenK("[TEST]: printLnFileLen"));
	printLnFileK(FILE_STDOUT, "[TEST]: printLnFileK");

	// --------------------------------------

	printFmt("[TEST]: printFmt int=%d, string=%s\n", 256, "\"TestString\"");
	printFmtFile(FILE_STDOUT, "[TEST]: printFmtFile int=%d, string=%s\n", 512, "\"Hahaha\"");
	printLnFmt("[TEST]: printFmtLn int=%d, string=%s", 768, "\"HelloStr\"");
	printLnFmtFile(FILE_STDOUT, "[TEST]: printLnFmtFile int=%d, string=%s", 1024, "\"FmtFile\"");

	// --------------------------------------

	const s8 s3[] = "1234567";
	printLnFmt("[TEST]: strlen=%d", strlen(s3));
	printLnFmt("[TEST]: strlenK=%d", strlenK(s3));

	// --------------------------------------

	return 0;
}