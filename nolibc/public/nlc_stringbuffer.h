#ifndef NOLIBC_STRINGBUFFER_H
#define NOLIBC_STRINGBUFFER_H

#include "nlc_iwriter.h"
#include "nlc_types.h"

typedef struct {
	s8* buf;
	u64 size;
	u64 len;
} StringBuffer;

void StringBufferPutc(StringBuffer* ctx, s8 c);
void StringBufferPuts(StringBuffer* ctx, const cStr str, u64 n);
IWriter StringBufferToIWriter(StringBuffer* sb);

#endif //NOLIBC_STRINGBUFFER_H