#include "public/nlc_stringbuffer.h"
#include "public/nlc_iwriter.h"
#include "public/nlc_types.h"

uSize FormatUnsignedToCStr(u64 value, const s8 base, cStr out, const u32 min_width) {
    u64 pos = 0;
    if (value == 0) {
        out[pos++] = '0';
    }
    else {
        while (value != 0) {
            const u64 rem = value % base;
            out[pos++] = rem < 10 ? '0' + rem : 'a' + (rem - 10);
            value /= base;
        }
        // reverse
        for (u64 i = 0, j = pos - 1; i < j; ++i, --j) {
            const s8 t = out[i];
            out[i] = out[j];
            out[j] = t;
        }
    }
    // pad if needed
    while (pos < min_width) {
        // shift right by one
        for (u64 i = pos; i > 0; --i) out[i] = out[i - 1];
        out[0] = '0';
        pos++;
    }
    return pos;
}

uSize FormatSignedToCStr(const s64 val, cStr out) {
    if (val < 0) {
        const u64 v = (u64)-val;
        const u64 len = FormatUnsignedToCStr(v, 10, out + 1, 0);
        out[0] = '-';
        return len + 1;
    }
    return FormatUnsignedToCStr((u64)val, 10, out, 0);
}

void FormatFloatToCStr(f64 value, cStr out, u64* outLen, const u32 precision) {
    u64 pos = 0;

    // handle sign
    if (value < 0) {
        out[pos++] = '-';
        value = -value;
    }

    // integer part
    const u64 integerPart = (u64)value;
    const u64 integerPartLen = FormatUnsignedToCStr(integerPart, 10, out + pos, 0);
    pos += integerPartLen;

    // decimal point
    out[pos++] = '.';

    // fractional part
    f64 frac = value - (f64)integerPart;
    for (u32 i = 0; i < precision; i++) {
        frac *= 10.0;
        const u32 digit = (u32)frac;
        if (digit >= 10) break;
        out[pos++] = (s8)('0' + digit);
        frac -= digit;
    }

    *outLen = pos;
}

u64 FormatCStrV(s8* buf, const u64 size, const cStr fmt, VaList vaList) {
	StringBuffer sb = { buf, size, 0 };
	const IWriter w = StringBufferToIWriter(&sb);
	IWriterFmtV(&w, fmt, vaList);
	if (buf) buf[sb.len] = '\0';
	return sb.len;
}

u64 FormatCStr(s8* buf, const u64 size, const cStr fmt, ...) {
	VaList vaList;
	VaStart(vaList, fmt);
	const u64 len = FormatCStrV(buf, size, fmt, vaList);
	VaEnd(vaList);
	return len;
}