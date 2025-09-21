#include "private/write_buffer.h"

#include "private/system.h"
#include "public/nlc_format.h"
#include "public/nlc_string.h"

// ============================
// MARK: Buffer
// ============================

void WriteBufferFlush(WriteBuffer* wb) {
    if (wb->len > 0) {
        SysWrite(wb->fd, (u8*)wb->data, wb->len);
        wb->len = 0;
    }
}

void WriteBufferPutc(WriteBuffer* wb, const s8 c) {
    if (wb->len >= OUTBUF_SIZE) WriteBufferFlush(wb);
    wb->data[wb->len++] = c;
}

void WriteBufferPuts(WriteBuffer* wb, const cStr str, const u64 n) {
    for (u64 i = 0; i < n; i++) {
        WriteBufferPutc(wb, str[i]);
    }
}

void WriteBufferFmtV(WriteBuffer* wb, const cStr fmt, vaList va) {
    const cStr p = fmt;
    s8 numBuff[64];

    while (*p) {
        if (*p != '%') {
            // find next % or end to batch writes
            const cStr start = p;
            while (*p && *p != '%') p++;
            WriteBufferPuts(wb, start, (u64)(p - start));
            continue;
        }
        // handle %
        p++; // skip '%'
        if (*p == '%') {
            WriteBufferPutc(wb, '%');
            p++;
            continue;
        }

        // optional width (simple, only decimal digits)
        int width = 0;
        while (*p >= '0' && *p <= '9') {
            width = width * 10 + (*p - '0');
            p++;
        }

        switch (*p) {
            case 'f': {
                const uPtr fptr = __builtin_va_arg(va, uPtr);
                const f64 f = *(f64*)fptr;
                u64 len = 0;
                FormatFloatToCStr(f, numBuff, &len, width == 0 ? 6 : width);
                WriteBufferPuts(wb, numBuff, len);
                break;
            }
            case 's': {
                const cStr s = __builtin_va_arg(va, const cStr);
                if (!s) s = (const cStr)"(null)";
                WriteBufferPuts(wb, s, cStrLen(s));
                break;
            }
            case 'd': {
                const s64 v = __builtin_va_arg(va, s64);
                const u64 len = FormatSignedToCStr(v, numBuff);
                WriteBufferPuts(wb, numBuff, len);
                break;
            }
            case 'u': {
                const u64 v = __builtin_va_arg(va, u64);
                const u64 len = FormatUnsignedToCStr(v, 10, numBuff, width);
                WriteBufferPuts(wb, numBuff, len);
                break;
            }
            case 'x': {
                const u64 v = __builtin_va_arg(va, u64);
                const u64 len = FormatUnsignedToCStr(v, 16, numBuff, width);
                WriteBufferPuts(wb, numBuff, len);
                break;
            }
            case 'c': {
                const sPtr ch = __builtin_va_arg(va, sPtr);
                WriteBufferPutc(wb, (s8)ch);
                break;
            }
            default:
                WriteBufferPutc(wb, '%');
                if (*p) WriteBufferPutc(wb, *p);
                else WriteBufferPutc(wb, '?');
                break;
        }
        if (*p) p++;
    }
}