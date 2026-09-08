#include "common.h"

void putchar(char ch);

void *memset(void *buf, char ch, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--) *p++ = ch;
    return buf;
}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *p = (uint8_t *) dst;
    const uint8_t *q = (const uint8_t *) src;
    while (n--) *p++ = *q++;
    return dst;
}

char *strcpy(char *dst, const char *src) {
    char *p = dst;
    while (*src) *p++ = *src++;
    *p = '\0';
    return dst;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2)
            break;
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);
    while (*fmt) {
        if (*fmt != '%')
            putchar(*fmt);
        else {
            fmt++;
            switch (*fmt) {
            case '\0':
                putchar('%');
                goto end;
            case '%':
                putchar('%');
                break;
            case 's':
                const char *str = va_arg(vargs, const char *);
                while (*str) putchar(*str++);
                break;
            case 'd':
                int num = va_arg(vargs, int);
                unsigned abs = num;
                if (num < 0) {
                    putchar('-');
                    abs = -abs;
                }
                unsigned div = 1;
                while (abs / div > 9) div *= 10;
                while (div > 0) {
                    putchar('0' + abs / div);
                    abs %= div;
                    div /= 10;
                }
                break;
            case 'x':
                unsigned value = va_arg(vargs, unsigned);
                for (int i = 7; i >= 0; i--) {
                    unsigned hex_digit = (value >> (i * 4)) & 0xf;
                    putchar("0123456789abcdef"[hex_digit]);
                }
                break;
            default:
                break;
            }
        }
        fmt++;
    }
end:
    va_end(vargs);
}