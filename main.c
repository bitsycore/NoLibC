#include <nlc.h>

int main() {

	// --------------------------------------

	Print("[TEST]: Print\n");
	PrintLen("[TEST]: PrintLen\n", StrLenK("[TEST]: PrintLen\n"));
	PrintK("[TEST]: PrintK\n");

	// --------------------------------------

	PrintFile(FILE_STDOUT, "[TEST]: PrintFile\n");
	PrintFileLen(FILE_STDOUT, "[TEST]: PrintFileLen\n", StrLenK("[TEST]: PrintFileLen\n"));
	PrintFileK(FILE_STDOUT, "[TEST]: PrintFileK\n");

	// --------------------------------------

	PrintLn("[TEST]: PrintLn");
	PrintLnLen("[TEST]: PrintLnLen", StrLenK("[TEST]: PrintLnLen"));
	PrintLnK("[TEST]: PrintLnK");

	// --------------------------------------

	PrintLnFile(FILE_STDOUT, "[TEST]: PrintLnFile");
	PrintLnFileLen(FILE_STDOUT, "[TEST]: PrintLnFileLen", StrLenK("[TEST]: PrintLnFileLen"));
	PrintLnFileK(FILE_STDOUT, "[TEST]: PrintLnFileK");

	// --------------------------------------

	PrintFmt("[TEST]: PrintFmt int=%d, string=%s\n", 256, "\"TestString\"");
	PrintFmtFile(FILE_STDOUT, "[TEST]: PrintFmtFile int=%d, string=%s\n", 512, "\"Hahaha\"");

	// --------------------------------------

	const s8 s3[] = "1234567";
	PrintFmt("[TEST]: StrLen=%d\n", StrLen(s3));
	PrintFmt("[TEST]: StrLenK=%d\n", StrLenK(s3));

	return 0;
}