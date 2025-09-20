#ifndef NOLIBC_WRITER_BUFFER_H
#define NOLIBC_WRITER_BUFFER_H

#include "public/nlc.h"

#define OUTBUF_SIZE 1024

typedef struct WriteBuffer {
    s8 data[OUTBUF_SIZE];
    u64 len;
    u64 fd;
} WriteBuffer;

void WriteBufferFlush(WriteBuffer* b);
void WriteBufferPutc(WriteBuffer* b, s8 c);
void WriteBufferPuts(WriteBuffer* b, const s8* s, u64 n);

#endif //NOLIBC_WRITER_BUFFER_H