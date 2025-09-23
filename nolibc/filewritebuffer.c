#include "public/nlc_filewritebuffer.h"

#include "private/system.h"
#include "public/nlc_iwriter.h"

static void FileWriteBuffer_IWriterPutc(void* ctx, const s8 c) {
	FileWriteBufferPutc(ctx, c);
}
static void FileWriteBuffer_IWriterPuts(void* ctx, const cStr str, const u64 n) {
	FileWriteBufferPuts(ctx, str, n);
}

IWriter FileWriteBufferToIWriter(FileWriteBuffer* wb) {
	return (IWriter) { FileWriteBuffer_IWriterPutc, FileWriteBuffer_IWriterPuts, wb };
}

void FileWriteBufferFlush(FileWriteBuffer* wb) {
    if (wb->len > 0) {
        SysWrite(wb->fd, (u8*)wb->data, wb->len);
        wb->len = 0;
    }
}

void FileWriteBufferPutc(FileWriteBuffer* wb, const s8 c) {
    if (wb->len >= OUTBUF_SIZE) FileWriteBufferFlush(wb);
    wb->data[wb->len++] = c;
}

void FileWriteBufferPuts(FileWriteBuffer* wb, const cStr str, const u64 n) {
    for (u64 i = 0; i < n; i++) {
        FileWriteBufferPutc(wb, str[i]);
    }
}

void FileWriteBufferFmt(FileWriteBuffer* wb, const cStr fmt, ...) {
    VaList ap;
    VaStart(ap, fmt);
    FileWriteBufferFmtV(wb, fmt, ap);
    VaEnd(ap);
}

void FileWriteBufferFmtV(FileWriteBuffer* wb, const cStr fmt, VaList vaList) {
	const IWriter w = { FileWriteBuffer_IWriterPutc, FileWriteBuffer_IWriterPuts, wb };
	IWriterFmtV(&w, fmt, vaList);
}