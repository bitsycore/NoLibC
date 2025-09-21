#include <nlc.h>

#define TPRE AC_GREEN "[TEST]" AC_RESET ": "

void testColor() {

	PrintLnK(TPRE "ANSI Color");
	PrintK(AC_BLACK  	"░▒▓█" 	AC_END);
	PrintK(AC_RED    	"░▒▓█" 	AC_END);
	PrintK(AC_GREEN  	"░▒▓█" 	AC_END);
	PrintK(AC_YELLOW 	"░▒▓█" 	AC_END);
	PrintK(AC_BLUE   	"░▒▓█" 	AC_END);
	PrintK(AC_MAGENTA	"░▒▓█" 	AC_END);
	PrintK(AC_CYAN   	"░▒▓█" 	AC_END);
	PrintK(AC_WHITE  	"░▒▓█" 	AC_END);
	PrintNewLine();
	PrintK(AC_BBLACK  	"░▒▓█" 	AC_END);
	PrintK(AC_BRED    	"░▒▓█" 	AC_END);
	PrintK(AC_BGREEN  	"░▒▓█" 	AC_END);
	PrintK(AC_BYELLOW 	"░▒▓█" 	AC_END);
	PrintK(AC_BBLUE   	"░▒▓█" 	AC_END);
	PrintK(AC_BMAGENTA	"░▒▓█" 	AC_END);
	PrintK(AC_BCYAN   	"░▒▓█" 	AC_END);
	PrintK(AC_BWHITE  	"░▒▓█" 	AC_END);
	PrintNewLine();

	PrintLnK(TPRE "ANSI Color BG");
	PrintK(AC_BG_BLACK  	"░░░░" 	AC_END);
	PrintK(AC_BG_RED    	"░░░░" 	AC_END);
	PrintK(AC_BG_GREEN  	"░░░░" 	AC_END);
	PrintK(AC_BG_YELLOW 	"░░░░" 	AC_END);
	PrintK(AC_BG_BLUE   	"░░░░" 	AC_END);
	PrintK(AC_BG_MAGENTA	"░░░░" 	AC_END);
	PrintK(AC_BG_CYAN   	"░░░░" 	AC_END);
	PrintK(AC_BG_WHITE  	"░░░░" 	AC_END);
	PrintNewLine();
	PrintK(AC_BG_BBLACK  	"░░░░" 	AC_END);
	PrintK(AC_BG_BRED    	"░░░░" 	AC_END);
	PrintK(AC_BG_BGREEN  	"░░░░" 	AC_END);
	PrintK(AC_BG_BYELLOW 	"░░░░" 	AC_END);
	PrintK(AC_BG_BBLUE   	"░░░░" 	AC_END);
	PrintK(AC_BG_BMAGENTA	"░░░░" 	AC_END);
	PrintK(AC_BG_BCYAN   	"░░░░" 	AC_END);
	PrintK(AC_BG_BWHITE  	"░░░░" 	AC_END);
	PrintNewLine();

	PrintLnK(TPRE "ANSI Text Styles");
	PrintLnK(				"AC_RESET: This is a text test.");
	PrintLnK(AC_BOLD 		"AC_BOLD: This is a text test." AC_END);
	PrintLnK(AC_FAINT 		"AC_FAINT: This is a text test." AC_END);
	PrintLnK(AC_ITALIC 		"AC_ITALIC: This is a text test." AC_END);
	PrintLnK(AC_UNDERLINE 	"AC_UNDERLINE: This is a text test." AC_END);
	PrintLnK(AC_BLINK 		"AC_BLINK: This is a text test." AC_END);
	PrintLnK(AC_RAPIDBLINK 	"AC_RAPIDBLINK: This is a text test." AC_END);
	PrintLnK(AC_REVERSE 	"AC_REVERSE: This is a text test." AC_END);
	PrintLnK(AC_CONCEAL 	"AC_CONCEAL: This is a text test." AC_END);
	PrintLnK(AC_STRIKE		"AC_STRIKE: This is a text test." AC_END);
	PrintLnK(AC_DOUBLEUNDER	"AC_DOUBLEUNDER: This is a text test." AC_END);
	PrintLnK(AC_NORMALINT	"AC_NORMALINT: This is a text test." AC_END);
	PrintLnK(AC_OVERLINE 	"AC_OVERLINE: This is a text test." AC_END);

	PrintLnK(TPRE "ANSI Color 256");
	PrintK(AC_FG256(16)		"░▒▓█" 	AC_END);
	PrintK(AC_FG256(24)		"░▒▓█" 	AC_END);
	PrintK(AC_FG256(32)		"░▒▓█" 	AC_END);
	PrintK(AC_FG256(40)		"░▒▓█" 	AC_END);
	PrintK(AC_FG256(48)		"░▒▓█" 	AC_END);
	PrintK(AC_FG256(56)		"░▒▓█" 	AC_END);
	PrintNewLine();
	PrintK(AC_FG256(64)		"░▒▓█" 	AC_END);
	PrintK(AC_FG256(72)		"░▒▓█" 	AC_END);
	PrintK(AC_FG256(80) 	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(88) 	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(96) 	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(104)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(112)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(120)	"░▒▓█" 	AC_END);
	PrintNewLine();
	PrintK(AC_FG256(128)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(136)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(144)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(152)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(160)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(168)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(176)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(184)	"░▒▓█" 	AC_END);
	PrintNewLine();
	PrintK(AC_FG256(192)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(200)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(208)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(216)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(224)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(232)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(240)	"░▒▓█" 	AC_END);
	PrintK(AC_FG256(248)	"░▒▓█" 	AC_END);
	PrintNewLine();

	PrintLnK(TPRE "ANSI Color BG 256");
	PrintK(AC_BG256(16)		"░░░░" 	AC_END);
	PrintK(AC_BG256(24)		"░░░░" 	AC_END);
	PrintK(AC_BG256(32)		"░░░░" 	AC_END);
	PrintK(AC_BG256(40)		"░░░░" 	AC_END);
	PrintK(AC_BG256(48)		"░░░░" 	AC_END);
	PrintK(AC_BG256(56)		"░░░░" 	AC_END);
	PrintNewLine();
	PrintK(AC_BG256(64)		"░░░░" 	AC_END);
	PrintK(AC_BG256(72)		"░░░░" 	AC_END);
	PrintK(AC_BG256(80)		"░░░░" 	AC_END);
	PrintK(AC_BG256(88)		"░░░░" 	AC_END);
	PrintK(AC_BG256(96)		"░░░░" 	AC_END);
	PrintK(AC_BG256(104)	"░░░░" 	AC_END);
	PrintK(AC_BG256(112)	"░░░░" 	AC_END);
	PrintK(AC_BG256(120)	"░░░░" 	AC_END);
	PrintNewLine();
	PrintK(AC_BG256(128)	"░░░░" 	AC_END);
	PrintK(AC_BG256(136)	"░░░░" 	AC_END);
	PrintK(AC_BG256(144)	"░░░░" 	AC_END);
	PrintK(AC_BG256(152)	"░░░░" 	AC_END);
	PrintK(AC_BG256(160)	"░░░░" 	AC_END);
	PrintK(AC_BG256(168)	"░░░░" 	AC_END);
	PrintK(AC_BG256(176)	"░░░░" 	AC_END);
	PrintK(AC_BG256(184)	"░░░░" 	AC_END);
	PrintNewLine();
	PrintK(AC_BG256(192)	"░░░░" 	AC_END);
	PrintK(AC_BG256(200)	"░░░░" 	AC_END);
	PrintK(AC_BG256(208)	"░░░░" 	AC_END);
	PrintK(AC_BG256(216)	"░░░░" 	AC_END);
	PrintK(AC_BG256(224)	"░░░░" 	AC_END);
	PrintK(AC_BG256(232)	"░░░░" 	AC_END);
	PrintK(AC_BG256(240)	"░░░░" 	AC_END);
	PrintK(AC_BG256(248)	"░░░░" 	AC_END);
	PrintNewLine();

	PrintLnK(TPRE "ANSI Color RGB");
	PrintK(AC_RGB_FG(128,000,000)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_FG(000,128,000)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_FG(000,000,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_FG(128,128,000)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_FG(000,128,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_FG(128,000,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_FG(128,128,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_FG(000,000,000)    "░▒▓█" 	AC_END);
	PrintNewLine();

	PrintLnK(TPRE "ANSI Color BG RGB");
	PrintK(AC_RGB_BG(128,000,000)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_BG(000,128,000)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_BG(000,000,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_BG(128,128,000)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_BG(000,128,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_BG(128,000,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_BG(128,128,128)    "░▒▓█" 	AC_END);
	PrintK(AC_RGB_BG(000,000,000)    "░▒▓█" 	AC_END);
	PrintNewLine();
}

void testFileWrite() {
	const Str filename = StrConst("testfile.txt");
	const Str message = StrConst(TPRE "FileOpen, FileWrite, FileClose, FileOpen, FileRead\n");
	u8 buffer[message.len];

	int fd = FileOpen(filename.str, OPEN_WRITE | OPEN_CREATE_IF_NEED | OPEN_TRUNCATE);
	if (fd < 0) Exit(1);
	FileWrite(fd, (u8*)message.str, message.len);
	FileClose(fd);

	fd = FileOpen(filename.str, OPEN_READ);
	if (fd < 0) Exit(1);
	const s64 result = FileSize(fd);
	PrintFmt(TPRE "FileSize=%d\n", result);
	const s64 n = FileRead(fd, buffer, sizeof(buffer));
	FileClose(fd);

	PrintLen((cStr)buffer, n);
}

void testPrintAndFormat(void) {
	Print(TPRE "Print\n");
	const Str printLenStr = StrConst(TPRE "PrintLen\n");
	PrintLen(printLenStr.str, printLenStr.len);
	PrintK(TPRE "PrintK\n");

	PrintLn(TPRE "PrintLn");
	const Str printLnLenStr = StrConst(TPRE "PrintLnLen");
	PrintLnLen(printLnLenStr.str, printLnLenStr.len);
	PrintLnK(TPRE "PrintLnK");

	PrintFmt(TPRE "PrintFmt int=%d, string=%s\n", 256, "\"TestString\"");
	FileWriteFmt(FILE_STDOUT, TPRE "PrintFmtFile int=%d, string=%s\n", 512, "\"Hahaha\"");
}

void testStrings(void) {
	const s8 s3[] = "1234567";
	const f64 f4 = 987.567123456789;
	PrintFmt(TPRE "cStrLen=%d\n", cStrLen(s3));
	PrintFmt(TPRE "cStrLenK=%d\n", cStrLenK(s3));
	PrintFmt(TPRE "PrintFmt with ptr, float=%9f\n", &f4);
}

void testMemory(void) {
	Arena* arenas[100];
	for (int i = 0; i < sizeof(arenas) / sizeof(arenas[0]); i++) {
		arenas[i] = ArenaNew(16 * 1024);
		if (i == 0) {
			const u64 remaining = ArenaRemaining(arenas[i]);
			PrintFmt(TPRE "ArenaRemaining Before remaining=%d\n", remaining);
		}
		u8* buffer = ArenaAlloc(arenas[i], 1024);
		MemorySet(buffer, 5, 1024);
		buffer = ArenaAlloc(arenas[i], 1024);
		if (i == 0) {
			const u64 remaining = ArenaRemaining(arenas[i]);
			PrintFmt(TPRE "ArenaRemaining After remaining=%d\n", remaining);
		}
		MemorySet(buffer, 7, 1024);
	}
	for (int i = 0; i < sizeof(arenas) / sizeof(arenas[0]); i++) {
		ArenaFree(arenas[i]);
	}

	PrintLnK(TPRE "ArenaNew, ArenaAlloc, ArenaReset, ArenaRemaining, ArenaFree");
}

int main(const int argc, char** argv) {
	(void)argc;
	(void)argv;

	testColor();
	testFileWrite();
	testPrintAndFormat();
	testStrings();
	testMemory();

	return 0;
}
