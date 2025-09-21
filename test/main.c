#include <nlc.h>

void fileWriteTest() {
	const Str filename = StrConst("testfile.txt");
	const Str message = StrConst("[TEST]: FileOpen, FileWrite, FileClose, FileOpen, FileRead\n");
	u8 buffer[message.len];

	int fd = FileOpen(filename.str, OPEN_WRITE | OPEN_CREATE_IF_NEED | OPEN_TRUNCATE);
	if (fd < 0) Exit(1);
	FileWrite(fd, (u8*)message.str, message.len);
	FileClose(fd);

	fd = FileOpen(filename.str, OPEN_READ);
	if (fd < 0) Exit(1);
	const s64 result = FileSize(fd);
	PrintFmt("[TEST]: FileSize=%d\n", result);
	const s64 n = FileRead(fd, buffer, sizeof(buffer));
	FileClose(fd);

	PrintLen((cStr)buffer, n);
}

int main() {
	// --------------------------------------

	fileWriteTest();

	// --------------------------------------

	Print("[TEST]: Print\n");
	PrintLen("[TEST]: PrintLen\n", cStrLenK("[TEST]: PrintLen\n"));
	PrintK("[TEST]: PrintK\n");

	// --------------------------------------

	PrintFile(FILE_STDOUT, "[TEST]: PrintFile\n");
	PrintFileLen(FILE_STDOUT, "[TEST]: PrintFileLen\n", cStrLenK("[TEST]: PrintFileLen\n"));
	PrintFileK(FILE_STDOUT, "[TEST]: PrintFileK\n");

	// --------------------------------------

	PrintLn("[TEST]: PrintLn");
	PrintLnLen("[TEST]: PrintLnLen", cStrLenK("[TEST]: PrintLnLen"));
	PrintLnK("[TEST]: PrintLnK");

	// --------------------------------------

	PrintLnFile(FILE_STDOUT, "[TEST]: PrintLnFile");
	PrintLnFileLen(FILE_STDOUT, "[TEST]: PrintLnFileLen", cStrLenK("[TEST]: PrintLnFileLen"));
	PrintLnFileK(FILE_STDOUT, "[TEST]: PrintLnFileK");

	// --------------------------------------

	PrintFmt("[TEST]: PrintFmt int=%d, string=%s\n", 256, "\"TestString\"");
	PrintFmtFile(FILE_STDOUT, "[TEST]: PrintFmtFile int=%d, string=%s\n", 512, "\"Hahaha\"");

	// --------------------------------------

	const s8 s3[] = "1234567";
	const f64 f4 = 987.567123456789;
	PrintFmt("[TEST]: cStrLen=%d\n", cStrLen(s3));
	PrintFmt("[TEST]: cStrLenK=%d\n", cStrLenK(s3));
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
		MemorySet(buffer, 5, 1024);
		buffer = ArenaAlloc(arenas[i], 1024);
		if (i == 0) {
			const u64 remaining = ArenaRemaining(arenas[i]);
			PrintFmt("[TEST]: ArenaRemaining After remaining=%d\n", remaining);
		}
		MemorySet(buffer, 7, 1024);
	}
	for (int i = 0; i < sizeof(arenas) / sizeof(arenas[0]); i++) {
		ArenaFree(arenas[i]);
	}

	PrintLnK("[TEST]: ArenaNew, ArenaAlloc, ArenaReset, ArenaRemaining, ArenaFree");

	return 0;
}