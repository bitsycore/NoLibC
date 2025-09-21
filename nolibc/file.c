#include "public/nlc_file.h"

#include "private/system.h"

int FileOpen(const cStr filename, const int flags) {
	return (int)SysOpen(filename, flags, 0644 /*rw-r--r--*/);
}

void FileClose(const int fd) {
	SysClose(fd);
}

s64 FileRead(const int fd, u8* buf, const uSize count) {
	return SysRead(fd, buf, count);
}

s64 FileWrite(const int fd, const u8* buf, const uSize count) {
	return SysWrite(fd, buf, count);
}

#if defined(__x86_64__)
	#define STAT_BUF_SIZE 144
	#define STAT_ST_SIZE_OFFSET 48
#elif defined(__i386__)
	#define STAT_BUF_SIZE 96
	#define STAT_ST_SIZE_OFFSET 36
#elif defined(__arm__)
	#define STAT_BUF_SIZE 96
	#define STAT_ST_SIZE_OFFSET 36
#elif defined(__aarch64__)
	#define STAT_BUF_SIZE 144
	#define STAT_ST_SIZE_OFFSET 48
#else
	#error "Architecture not supported"
#endif

sSize FileSize(const int fd) {
	const s64 cur = SysLSeek(fd, 0, SEEK_CUR);
	const s64 size = SysLSeek(fd, 0, SEEK_END);
	SysLSeek(fd, cur, SEEK_SET);
#if defined(__APPLE__)
	return size;
#elif defined(__linux__)
	if (size >= 0) return size;
	u8 buf[STAT_BUF_SIZE];
	if (SysFStat(fd, buf) < 0) return -1;
	return *(s64*)(buf + STAT_ST_SIZE_OFFSET);
#endif
}