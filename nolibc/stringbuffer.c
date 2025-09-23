#include "public/nlc_stringbuffer.h"

void StringBufferPutc(StringBuffer* ctx, const s8 c) {
	StringBuffer* sb = ctx;
	if (!sb) return;
	if (sb->buf == null) {
		if (sb->len < sb->size - 1) sb->len++;
	} else {
		if (sb->len < sb->size - 1) sb->buf[sb->len++] = c;
	}
}

void StringBufferPuts(StringBuffer* ctx, const cStr str, const u64 n) {
	StringBuffer* sb = ctx;
	if (!sb) return;
	for (u64 i = 0; i < n && sb->len < sb->size - 1; i++) {
		if (sb->buf == null) {
			sb->len++;
		} else {
			sb->buf[sb->len++] = str[i];
		}
	}
}

static void StringBuffer_IWriterPutc(void* ctx, const s8 c) {
	StringBufferPutc(ctx, c);
}

static void StringBuffer_IWriterPuts(void* ctx, const cStr str, const u64 n) {
	StringBufferPuts(ctx, str, n);
}

IWriter StringBufferToIWriter(StringBuffer* sb) {
	return (IWriter) { StringBuffer_IWriterPutc, StringBuffer_IWriterPuts, sb };
}