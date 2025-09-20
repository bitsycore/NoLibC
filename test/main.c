#include <nlc.h>

void fileWriteTest() {
	#define FILENAME "testfile.txt"
	#define MESSAGE "[TEST]: FileOpen, FileWrite, FileClose, FileOpen, FileRead\n"
	u8 buffer[128];

	s64 fd = FileOpen(FILENAME, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0) Exit(1);
	FileWrite(fd, (u8*)MESSAGE, StrLenK(MESSAGE));
	FileClose(fd);

	fd = FileOpen(FILENAME, O_RDONLY);
	if (fd < 0) Exit(1);
	const s64 result = FileSize(fd);
	PrintFmt("[TEST]: FileSize=%d\n", result);
	const s64 n = FileRead(fd, buffer, sizeof(buffer));
	FileClose(fd);

	PrintLen((s8*)buffer, n);
	#undef FILENAME
	#undef MESSAGE
}

int main() {
	// --------------------------------------

	fileWriteTest();

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

	// --------------------------------------

	Arena* arenas[100];
	for (int i = 0; i < sizeof(arenas) / sizeof(arenas[0]); i++) {
		arenas[i] = ArenaNew(16 * 1024);
		if (i == 0) {
			const u64 remaining = ArenaRemaining(arenas[i]);
			PrintFmt("[TEST]: ArenaRemaining Before remaining=%d\n", remaining);
		}
		u8* buffer = ArenaAlloc(arenas[i], 1024);
		Memset(buffer, 5, 1024);
		buffer = ArenaAlloc(arenas[i], 1024);
		if (i == 0) {
			const u64 remaining = ArenaRemaining(arenas[i]);
			PrintFmt("[TEST]: ArenaRemaining After remaining=%d\n", remaining);
		}
		Memset(buffer, 7, 1024);
	}
	for (int i = 0; i < sizeof(arenas) / sizeof(arenas[0]); i++) {
		ArenaFree(arenas[i]);
	}

	PrintLnK("[TEST]: ArenaNew, ArenaAlloc, ArenaReset, ArenaRemaining, ArenaFree");

	return 0;
}