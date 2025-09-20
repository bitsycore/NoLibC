#include <nlc.h>

void fileWriteTest() {
	const s8 filename[] = "testfile.txt";
	const s8 message[] = "[TEST]: FileOpen, FileWrite, FileClose, FileOpen, FileRead\n";
	u8 buffer[1024];

	// Open file for writing (create/truncate)
	s64 fd = FileOpen(filename, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0) Exit(1);

	// Write to file
	FileWrite(fd, (u8*)message, sizeof(message) / sizeof(message[0]) - 1);
	FileClose(fd);

	// Open file for reading
	fd = FileOpen(filename, O_RDONLY);
	if (fd < 0) Exit(1);

	const s64 result = FileSize(fd);
	PrintFmt("[TEST]: FileSize=%d\n", result);

	// Read from file
	const s64 n = FileRead(fd, buffer, sizeof(buffer));
	FileClose(fd);


	// Write read data to stdout
	PrintLen((s8*)buffer, n);
}

int main() {

	// --------------------------------------

	fileWriteTest();

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