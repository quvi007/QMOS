#include "common.h"

void putchar(char ch);

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