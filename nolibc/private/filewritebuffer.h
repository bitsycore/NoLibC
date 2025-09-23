#ifndef NOLIBC_WRITER_BUFFER_H
#define NOLIBC_WRITER_BUFFER_H

#include "../public/nlc_types.h"
#include "../public/nlc_varg.h"

#define OUTBUF_SIZE 1024

typedef struct WriteBuffer {
    s8 data[OUTBUF_SIZE];
    u64 len;
    u64 fd;
} FileWriteBuffer;

void FileWriteBufferFlush(FileWriteBuffer* wb);
void FileWriteBufferPutc(FileWriteBuffer* wb, s8 c);
void FileWriteBufferPuts(FileWriteBuffer* wb, const cStr str, uSize n);
void FileWriteBufferFmtV(FileWriteBuffer* wb, const cStr fmt, VaList vaList);

#endif //NOLIBC_WRITER_BUFFER_H