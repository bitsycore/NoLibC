#ifndef NOLIBC_IWRITER_H
#define NOLIBC_IWRITER_H

#include "nlc_types.h"
#include "nlc_varg.h"

typedef struct IWriter {
	void (*putc)(void* ctx, s8 c);
	void (*puts)(void* ctx, const cStr str, u64 n);
	void* ctx;
} IWriter;

void IWriterFmt(const IWriter* w, const cStr fmt, ...);
void IWriterFmtV(const IWriter* w, const cStr fmt, VaList vaList);

#endif //NOLIBC_IWRITER_H