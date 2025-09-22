#include <nlc.h>

#include "nolibc/private/system.h"

#define MIN(a, b)      ((a) < (b) ? (a) : (b))
#define MAX(a, b)      ((a) > (b) ? (a) : (b))
#define CLAMP(x, lo, hi)  ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))
#define TPRE AC_GREEN "[TEST]" AC_RESET ": "

NLC_ATTR_NO_INLINE
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

NLC_ATTR_NO_INLINE
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

NLC_ATTR_NO_INLINE
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

NLC_ATTR_NO_INLINE
void testStrings(void) {
	const s8 s3[] = "1234567";
	const f64 f4 = 987.567123456789;
	PrintFmt(TPRE "cStrLen=%d\n", cStrLen(s3));
	PrintFmt(TPRE "cStrLenK=%d\n", cStrLenK(s3));
	PrintFmt(TPRE "PrintFmt with ptr, float=%9f\n", &f4);
}

NLC_ATTR_NO_INLINE
void testArena(void) {
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

#define TCGETS 0x5401
#define TCSETS 0x5402
#define TIOCGWINSZ 0x5413

struct NLC_ATTR_PACKED termios {
	unsigned int	c_iflag;
	unsigned int	c_oflag;
	unsigned int	c_cflag;
	unsigned int	c_lflag;
	char			c_line;
	char			c_cc[32];
	unsigned int	c_ispeed;
	unsigned int	c_ospeed;
};

struct NLC_ATTR_PACKED winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};

// c_lflag
#define ICANON  0x0002
#define ECHO    0x0008
#define ISIG    0x0001
#define IEXTEN  0x8000

// c_iflag
#define ICRNL   0000400
#define INPCK   0000020
#define ISTRIP  0000040
#define IXON    0002000

// c_oflag
#define OPOST   0000001

// c_cflag
#define CS8     0000060

// c_cc index
#define VMIN    6
#define VTIME   5

void terminalSetRawMode(struct termios* orig) {
	struct termios edited;
	SysCall(SYS_ioctl, FILE_STDIN, TCGETS, (uPtr)orig, 0, 0, 0);
	edited = *orig;

	// Disable canonical mode, echo, signals, extended processing
	edited.c_lflag &= ~(ICANON | ECHO | ISIG );

	// Disable CR-to-NL translation, parity check, strip, flow control
	//edited.c_iflag &= ~(ICRNL | INPCK | ISTRIP | IXON);

	// Disable all output processing
	//edited.c_oflag &= ~(OPOST);

	// Set 8-bit chars
	//edited.c_cflag |= (CS8);

	// Minimum of 1 byte, no timeout
	edited.c_cc[VMIN]  = 1;
	edited.c_cc[VTIME] = 0;

	SysCall(SYS_ioctl, FILE_STDIN, TCSETS, (uPtr)&edited, 0, 0, 0);
}

void terminalRestore(struct termios *orig) { SysCall(SYS_ioctl, FILE_STDIN, TCSETS, (uPtr)orig, 0, 0, 0); }

void terminalClearScreen(void) {
	FileWrite(FILE_STDOUT, (u8*)StrParamLen("\033[H\033[J"));
}

void terminalSetCursor(const int x, const int y) {
	FileWriteFmt(FILE_STDOUT, "\033[%d;%dH", y+1, x+1);
}

void terminalRenderScreen(s8* screen, const uSize width, const uSize height) {
	terminalSetCursor(0, 0);
	for (uSize y = 0; y < height; y++) {
		FileWrite(FILE_STDOUT, (u8*)screen+(y*width), width);
		FileWrite(FILE_STDOUT, (u8*)StrParamLen("\n"));
	}
}

void terminalDrawChar(const s8 c) {
	FileWrite(FILE_STDOUT, (u8*)&c, 1);
}

NLC_ATTR_PRINTF(1, 6)
void terminalLog(const s8* message, const int cursor_x, const int cursor_y, const int width, const int height, ...) {
	terminalSetCursor(0, height);
	s8 blank[width];
	MemorySet(blank, ' ', width);
	FileWrite(FILE_STDOUT, (u8*)blank, width);
	terminalSetCursor(0, height);
	vaList args;
	__builtin_va_start(args, height);
	FileWriteFmtV(FILE_STDOUT, (s8*)message, args);
	__builtin_va_end(args);
	terminalSetCursor(cursor_x, cursor_y);
}

void FIXMEtestTerminal(void) {
	struct termios orig;
	terminalSetRawMode(&orig);

	struct winsize ws;
	const sPtr result = SysCall(SYS_ioctl, FILE_STDOUT, TIOCGWINSZ, (uPtr)&ws, 0, 0, 0);
	int HEIGHT, WIDTH;
	if (result < 0) {
		HEIGHT = 24;
		WIDTH = 80;
	} else {
		HEIGHT = ws.ws_row;
		WIDTH = ws.ws_col > 120 ? 120 : ws.ws_col;
	}
	s8 screen[HEIGHT][WIDTH];
	MemorySet(&screen, ' ', sizeof(screen));
	MemorySet(&screen[0], '-', WIDTH);
	MemorySet(&screen[HEIGHT-1], '-', WIDTH);
	for (uSize y = 1; y < HEIGHT-1; y++) {
		screen[y][0] = '|';
		screen[y][WIDTH-1] = '|';
	}
	screen[HEIGHT/2][WIDTH/2] = 'X';

	int cursor_x=1, cursor_y=1;

	terminalClearScreen();
	terminalRenderScreen((s8*)&screen, WIDTH, HEIGHT);
	u8 buf[1] = {0};
    while(1){
    	terminalSetCursor(cursor_x, cursor_y);

    	// KEYBOARD INPUT

        if(FileRead(FILE_STDIN, buf, 1)<=0) continue;

        const s8 c = (s8)buf[0];
        if(c==3) break; // End of Text // Ctrl-C
		if(c==127/*DEL*/||c==8/*Backspace*/){
			if(cursor_x>0) {
				cursor_x = MAX(1, cursor_x-1);
				screen[cursor_y][cursor_x]=' ';
				terminalSetCursor(cursor_x, cursor_y);
				terminalDrawChar(screen[cursor_y][cursor_x]);
			}
			terminalLog("[%d, %d], lastKey=BACKSPACE", cursor_x, cursor_y, WIDTH, HEIGHT, cursor_x, cursor_y);
		}
		else if(c>=32 && c<=126){ // Printable
			screen[cursor_y][cursor_x] = c;
			terminalDrawChar(screen[cursor_y][cursor_x]);
			cursor_x = MIN(WIDTH-2, cursor_x+1);
			terminalLog("[%d, %d], lastKey=%c", cursor_x, cursor_y, WIDTH, HEIGHT, cursor_x, cursor_y, buf[0]);
		}
    	// arrow keys
		else if(c==27){
			s8 seq[2];
			if(FileRead(FILE_STDIN, (u8*)&seq[0], 1)==0) continue;
			if(FileRead(FILE_STDIN, (u8*)&seq[1], 1)==0) continue;
			if(seq[0]=='['){
				if(seq[1]=='A') {
					cursor_y = MAX(cursor_y-1, 1); // up
					terminalLog("[%d, %d], lastKey=UP", cursor_x, cursor_y, WIDTH, HEIGHT, cursor_x, cursor_y);
				}
				else if(seq[1]=='D') {
					cursor_x = MAX(cursor_x-1, 1); // left
					terminalLog("[%d, %d], lastKey=LEFT", cursor_x, cursor_y, WIDTH, HEIGHT, cursor_x, cursor_y);
				}
				else if(seq[1]=='B') {
					cursor_y = MIN(cursor_y+1, HEIGHT-2); // down
					terminalLog("[%d, %d], lastKey=DOWN", cursor_x, cursor_y, WIDTH, HEIGHT, cursor_x, cursor_y);
				}
				else if(seq[1]=='C') {
					cursor_x = MIN(cursor_x+1, WIDTH-2); // right
					terminalLog("[%d, %d], lastKey=RIGHT", cursor_x, cursor_y, WIDTH, HEIGHT, cursor_x, cursor_y);
				}
			}
		}
	}

    terminalClearScreen();
	terminalRestore(&orig);
}

NLC_ATTR_NO_INLINE
int main(const int argc, char** argv) {
	(void)argc;
	(void)argv;

	//FIXMEtestTerminal();
	//return 0;
	testColor();
	testFileWrite();
	testPrintAndFormat();
	testStrings();
	testArena();

	return 0;
}
