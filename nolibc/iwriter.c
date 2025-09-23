//
// Created by Doge on 23/09/2025.
//

#include "public/nlc_iwriter.h"

#include "public/nlc_format.h"
#include "public/nlc_string.h"

void IWriterFmt(const IWriter* w, const cStr fmt, ...) {
	VaList vaList;
	VaStart(vaList, fmt);
	IWriterFmtV(w, fmt, vaList);
	VaEnd(vaList);
}

void IWriterFmtV(const IWriter* w, const cStr fmt, VaList vaList) {
    const cStr p = fmt;
    s8 numBuff[64];

    while (*p) {
        if (*p != '%') {
            const cStr start = p;
            while (*p && *p != '%') p++;
            w->puts(w->ctx, start, (u64)(p - start));
            continue;
        }
        p++;
        if (*p == '%') {
            w->putc(w->ctx, '%');
            p++;
            continue;
        }
        int width = 0;
        while (*p >= '0' && *p <= '9') {
            width = width * 10 + (*p - '0');
            p++;
        }
        switch (*p) {
            case 'f': {
                const double flot = VaArg(vaList, double);
                const f64 f = flot;
                u64 len = 0;
                FormatFloatToCStr(f, numBuff, &len, width == 0 ? 6 : width);
                w->puts(w->ctx, numBuff, len);
                break;
            }
            case 's': {
                const cStr s = VaArg(vaList, const cStr);
                if (!s) s = (const cStr)"(null)";
                w->puts(w->ctx, s, cStrLen(s));
                break;
            }
            case 'd': {
                const s64 v = VaArg(vaList, s64);
                const u64 len = FormatSignedToCStr(v, numBuff);
                w->puts(w->ctx, numBuff, len);
                break;
            }
            case 'u': {
                const u64 v = VaArg(vaList, u64);
                const u64 len = FormatUnsignedToCStr(v, 10, numBuff, width);
                w->puts(w->ctx, numBuff, len);
                break;
            }
            case 'x': {
                const u64 v = VaArg(vaList, u64);
                const u64 len = FormatUnsignedToCStr(v, 16, numBuff, width);
                w->puts(w->ctx, numBuff, len);
                break;
            }
            case 'c': {
                const sPtr ch = VaArg(vaList, sPtr);
                w->putc(w->ctx, (s8)ch);
                break;
            }
            default:
                w->putc(w->ctx, '%');
                if (*p) w->putc(w->ctx, *p);
                else w->putc(w->ctx, '?');
                break;
        }
        if (*p) p++;
    }
}