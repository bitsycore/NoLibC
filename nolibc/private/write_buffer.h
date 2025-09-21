#ifndef NOLIBC_WRITER_BUFFER_H
#define NOLIBC_WRITER_BUFFER_H

#include "../public/nlc_types.h"

#define OUTBUF_SIZE 1024

typedef struct WriteBuffer {
    s8 data[OUTBUF_SIZE];
    u64 len;
    u64 fd;
} WriteBuffer;

void WriteBufferFlush(WriteBuffer* wb);
void WriteBufferPutc(WriteBuffer* wb, s8 c);
void WriteBufferPuts(WriteBuffer* wb, const cStr str, uSize n);
void WriteBufferFmtV(WriteBuffer* wb, const cStr fmt, vaList va);

#endif //NOLIBC_WRITER_BUFFER_H