#include "priv_nolibc.h"
#include "../nolibc.h"

u64 strlen(const s8* s) {
	u64 n = 0;
	while (s[n] != '\0') n++;
	return n;
}