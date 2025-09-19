#include "_write_buffer.h"
#include "_syscall.h"

// ============================
// MARK: Buffer
// ============================

void WriteBufferFlush(WriteBuffer* b) {
    if (b->len > 0) {
        SysWrite(b->fd, (u8*)b->data, b->len);
        b->len = 0;
    }
}

void WriteBufferPutc(WriteBuffer* b, const s8 c) {
    if (b->len >= OUTBUF_SIZE) WriteBufferFlush(b);
    b->data[b->len++] = c;
}

void WriteBufferPuts(WriteBuffer* b, const s8* s, const u64 n) {
    for (u64 i = 0; i < n; i++) {
        WriteBufferPutc(b, s[i]);
    }
}