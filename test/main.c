#include <nlc.h>

int main() {

	// --------------------------------------

	Arena* arenas[100];
	for (int i = 0; i < sizeof(arenas) / sizeof(arenas[0]); i++) {
		arenas[i] = ArenaNew(16 * 1024);
		u8* buffer = ArenaAlloc(arenas[i], 1333);
		Memset(buffer, 5, 1333);
		buffer = ArenaAlloc(arenas[i], 1333);
		Memset(buffer, 7, 1333);
	}
	for (int i = 0; i < sizeof(arenas) / sizeof(arenas[0]); i++) {
		ArenaFree(arenas[i]);
	}

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
	const f64 f4 = 987.567123456789;
	PrintFmt("[TEST]: StrLen=%d\n", StrLen(s3));
	PrintFmt("[TEST]: StrLenK=%d\n", StrLenK(s3));
	PrintFmt("[TEST]: PrintFmt with ptr, float=%9f\n", &f4);

	return 0;
}